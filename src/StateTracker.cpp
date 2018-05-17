/*
 * StateTracker.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#include "StateTracker.h"
#include "utils/ErrorHandler.h"
#include "thread/LockGuard.h"

#define _USE_MATH_DEFINES
#include <cmath>

using std::sqrt;
using std::atan2;
using std::asin;
using std::cos;
using std::sin;
using std::tan;
using std::pow;


StateTracker::StateTracker()
{
    m_R.push_back(1);
    m_R.push_back(0);
    m_R.push_back(0);

    m_R.push_back(0);
    m_R.push_back(1);
    m_R.push_back(0);

    m_R.push_back(0);
    m_R.push_back(0);
    m_R.push_back(1);

    for(int i = 0; i < 3; i++)
    {
        m_accelCounter[i] = 0;
        m_biasFilter[i] = 0;
    }
}


StateTracker::~StateTracker()
{
}


void StateTracker::threadRoutine()
{
    initializeOrientation();

    while(true)
    {
        SensorData readings = m_sensors.getSensorData();
        updateState(readings);

        usleep(7100);   // Sample time is 10ms but due to processing time the sleep is reduced to get ~100 Hz
    }
}


void StateTracker::initializeOrientation()
{
    SensorData Initial = m_sensors.getSensorData();

    float g = atan2((float)Initial.Accelerometer.Y, (float)Initial.Accelerometer.Z);
    float b = asin(-(float)Initial.Accelerometer.X/GMAG);
    float a = 0;

    std::vector<float> temp = createRotationMatrix(a, b, g);
    m_R = multiplyRMatrix(m_R, temp);

//    CurrentState.RPY.pitch = g;
//    CurrentState.RPY.roll = b;
//    if(!sem_wait(&Access))
//    {
//        LastState = CurrentState;
//        sem_post(&Access);
//    }

    //Add functionality to gain initial rotation speeds as well
}


void StateTracker::updateState(SensorData data)
{
    m_currentState.m_angVelocity.roll = (data.Gyro.Y - GYROY_BIAS)*GYRO_SCALE_FCTR*RADIANS;
    m_currentState.m_angVelocity.pitch = (data.Gyro.X - GYROX_BIAS)*GYRO_SCALE_FCTR*RADIANS;
    m_currentState.m_angVelocity.yaw = (data.Gyro.Z - GYROZ_BIAS)*GYRO_SCALE_FCTR*RADIANS;

    // Calculate the relative alpha, beta, and gamma angles that the vehicle has rotated through
    // during the last timestep
    float a = m_currentState.m_angVelocity.yaw*DELTA_T;
    float b = m_currentState.m_angVelocity.roll*DELTA_T;
    float g = m_currentState.m_angVelocity.pitch*DELTA_T;

    // Creates the rotation matrix for the amount of rotation that has occured during the last timestep
    // It then takes this rotation and multiplies it against the global frame to update the global
    // position and orientation of the vehicle
    std::vector<float> latestRelativeRotation = createRotationMatrix(a, b, g);
    m_R = multiplyRMatrix(m_R, latestRelativeRotation);

    // Given the vehicle's current global orientation, calculate the amount of gravity that should be measured
    // by the accelerometer along its X, Y, and Z axes.  GMAG is in sensor units (mGs or milli-Gs)
    float xg = m_R[6]*GMAG;
    float yg = m_R[7]*GMAG;
    float zg = m_R[8]*GMAG;

    // Remove gravity from the accelerometer's measurements so that only the acceleration due to motion remains
    m_currentState.m_acceleration.x = data.Accelerometer.X - xg;
    m_currentState.m_acceleration.y = data.Accelerometer.Y - yg;
    m_currentState.m_acceleration.z = data.Accelerometer.Z - zg;

    std::vector<float> p(3, 0);

    p[0] = m_currentState.m_acceleration.x;
    p[1] = m_currentState.m_acceleration.y;
    p[2] = m_currentState.m_acceleration.z;

    // Convert the acceleration measured in the vehicle's coordinate frame to the global coordinate frame
    p = multiplyPosition(m_R, p);

    m_currentState.m_acceleration.x = p[0];
    m_currentState.m_acceleration.y = p[1];
    m_currentState.m_acceleration.z = p[2];

    m_currentState.m_angPosition.roll = atan2(-m_R[6], sqrt(pow(m_R[0],2) + pow(m_R[3],2)));
    m_currentState.m_angPosition.yaw = atan2(m_R[3]/cos(m_currentState.m_angPosition.roll), m_R[0]/cos(m_currentState.m_angPosition.roll));
    m_currentState.m_angPosition.pitch = atan2(m_R[7]/cos(m_currentState.m_angPosition.roll), m_R[8]/cos(m_currentState.m_angPosition.roll));

    // Pointers are used because in the following filter, a "++" operation is used to iterate through the struct
    float *accel, *vel, *pos;

    accel = &m_currentState.m_acceleration.x;
    vel = &m_currentState.m_velocity.x;
    pos = &m_currentState.m_displacement.x;

    float *lastaccel, *lastvel, *lastpos;

    lastaccel = &m_lastState.m_acceleration.x;
    lastvel = &m_lastState.m_velocity.x;
    lastpos = &m_lastState.m_displacement.x;

    // Begin Acceleration processing
    for(int i = 0; i < 3; i++)
    {
        // Converts sensor reading from mGs to m/s^2, then applies digital low pass filter to remove noise
        *accel = (*accel)*ACCEL_SCALE_FCTR*G_CONVERSION;
        *accel = *lastaccel + (*accel - *lastaccel)*ALPHA;

        // A heavier low pass filter is used in an attempt to remove the bias/drift from the sensor
        m_biasFilter[i] = m_biasFilter[i] + (*accel - m_biasFilter[i])*HEAVY_ALPHA;
        *accel = *accel - m_biasFilter[i];

        // Since between the bias filter and the orientation correction the vehicle's signal still resulted
        // in significant amounts of drift, a final assumption was made that the vehicle's movement
        // would either be starting or stopping, and that any periods of measured constant velocity are inaccurate
        // and should be reported as 0 m/s
        //
        // This next section adjusts the vehicle's speed back down to 0 if the change in acceleration has been
        // minimal over the last 33 samples (~1/3 of a second).  It uses a P loop to bring the velocity to 0
        // using the error in the vehicle's velocity as compared to 0 multiplied by the gain of P to adjust the
        // acceleration
        if((*accel - *lastaccel) < 0.05 )
        {
            m_accelCounter[i]++;
        }
        else
        {
            m_accelCounter[i] = 0;
        }

        float adjustedAccel = *accel;

        if(m_accelCounter[i] >= 33)
        {
            float error = (-(*lastvel));
            adjustedAccel = error*P;
        }

        *vel = *lastvel + adjustedAccel*DELTA_T;
        *pos = *lastpos + (*vel)*DELTA_T;

        accel++;
        vel++;
        pos++;

        lastaccel++;
        lastvel++;
        lastpos++;
    }


    {
        LockGuard guard(m_access);
        m_lastState = m_currentState;
    }
}


std::vector<float> StateTracker::createRotationMatrix(float a, float b, float g)
{
    std::vector<float> R;

    R.push_back(cos(a)*cos(b));
    R.push_back(cos(a)*sin(b)*sin(g) - sin(a)*cos(g));
    R.push_back(cos(a)*sin(b)*cos(g) + sin(a)*sin(g));

    R.push_back(sin(a)*cos(b));
    R.push_back(sin(a)*sin(b)*sin(g) + cos(a)*cos(g));
    R.push_back(sin(a)*sin(b)*cos(g) - cos(a)*sin(g));

    R.push_back(-sin(b));
    R.push_back(cos(b)*sin(g));
    R.push_back(cos(b)*cos(g));

    return R;
}


std::vector<float> StateTracker::multiplyRMatrix(std::vector<float> R, std::vector<float> Rb)
{
    std::vector<float> ReturnedMatrix(9, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                ReturnedMatrix[i*3 + j] += R[i*3 + k] * Rb[j + k*3];

    return ReturnedMatrix;
}


std::vector<float> StateTracker::multiplyPosition(std::vector<float> R, std::vector<float> p)
{
    std::vector<float> ReturnedMatrix(3, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ReturnedMatrix[i] += R[i*3 + j] * p[j];

    return ReturnedMatrix;
}


State StateTracker::getCurrentState()
{
    LockGuard guard(m_access);
    return m_lastState;
}
