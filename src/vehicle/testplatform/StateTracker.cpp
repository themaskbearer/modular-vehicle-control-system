/*
 * StateTracker.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#include "utils/ErrorLogger.h"
#include "StateTracker.h"
#include "utils/MatrixOperations.h"

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
    _R.push_back(1);
    _R.push_back(0);
    _R.push_back(0);

    _R.push_back(0);
    _R.push_back(1);
    _R.push_back(0);

    _R.push_back(0);
    _R.push_back(0);
    _R.push_back(1);

    for(int i = 0; i < 3; i++)
    {
        _accelCounter[i] = 0;
        _biasFilter[i] = 0;
    }
}


StateTracker::~StateTracker()
{
}


void StateTracker::threadRoutine()
{
    initializeOrientation();

    while(isRunning())
    {
        SensorData readings = _sensors.getSensorData();
        updateState(readings);

        // TODO: Make this calculation dynamic
        // Sample time is 10ms but due to processing time the sleep is reduced to get ~100 Hz
        std::this_thread::sleep_for(std::chrono::microseconds(7100));
    }
}


void StateTracker::initializeOrientation()
{
    SensorData Initial = _sensors.getSensorData();

    float g = atan2((float)Initial.Accelerometer.Y, (float)Initial.Accelerometer.Z);
    float b = asin(-(float)Initial.Accelerometer.X/GMAG);
    float a = 0;

    matrix::Matrix temp = matrix::createRotationMatrix(a, b, g);
    _R = matrix::multiplyRMatrix(_R, temp);

//    CurrentState.RPY.pitch = g;
//    CurrentState.RPY.roll = b;
//    if(!se_wait(&Access))
//    {
//        LastState = CurrentState;
//        se_post(&Access);
//    }

    //Add functionality to gain initial rotation speeds as well
}


void StateTracker::updateState(SensorData data)
{
    _currentState._angVelocity.roll = (data.Gyro.Y - GYROY_BIAS)*GYRO_SCALE_FCTR*RADIANS;
    _currentState._angVelocity.pitch = (data.Gyro.X - GYROX_BIAS)*GYRO_SCALE_FCTR*RADIANS;
    _currentState._angVelocity.yaw = (data.Gyro.Z - GYROZ_BIAS)*GYRO_SCALE_FCTR*RADIANS;

    // Calculate the relative alpha, beta, and gamma angles that the vehicle has rotated through
    // during the last timestep
    float a = _currentState._angVelocity.yaw*DELTA_T;
    float b = _currentState._angVelocity.roll*DELTA_T;
    float g = _currentState._angVelocity.pitch*DELTA_T;

    // Creates the rotation matrix for the amount of rotation that has occured during the last timestep
    // It then takes this rotation and multiplies it against the global frame to update the global
    // position and orientation of the vehicle
    matrix::Matrix latestRelativeRotation = matrix::createRotationMatrix(a, b, g);
    _R = matrix::multiplyRMatrix(_R, latestRelativeRotation);

    // Given the vehicle's current global orientation, calculate the amount of gravity that should be measured
    // by the accelerometer along its X, Y, and Z axes.  GMAG is in sensor units (mGs or milli-Gs)
    float xg = _R[6]*GMAG;
    float yg = _R[7]*GMAG;
    float zg = _R[8]*GMAG;

    // Remove gravity from the accelerometer's measurements so that only the acceleration due to motion remains
    _currentState._acceleration.x = data.Accelerometer.X - xg;
    _currentState._acceleration.y = data.Accelerometer.Y - yg;
    _currentState._acceleration.z = data.Accelerometer.Z - zg;

    matrix::Matrix p(3, 0);

    p[0] = _currentState._acceleration.x;
    p[1] = _currentState._acceleration.y;
    p[2] = _currentState._acceleration.z;

    // Convert the acceleration measured in the vehicle's coordinate frame to the global coordinate frame
    p = matrix::multiplyPosition(_R, p);

    _currentState._acceleration.x = p[0];
    _currentState._acceleration.y = p[1];
    _currentState._acceleration.z = p[2];

    _currentState._angPosition.roll = atan2(-_R[6], sqrt(pow(_R[0],2) + pow(_R[3],2)));
    _currentState._angPosition.yaw = atan2(_R[3]/cos(_currentState._angPosition.roll), _R[0]/cos(_currentState._angPosition.roll));
    _currentState._angPosition.pitch = atan2(_R[7]/cos(_currentState._angPosition.roll), _R[8]/cos(_currentState._angPosition.roll));

    // Pointers are used because in the following filter, a "++" operation is used to iterate through the struct
    float *accel, *vel, *pos;

    accel = &_currentState._acceleration.x;
    vel = &_currentState._velocity.x;
    pos = &_currentState._displacement.x;

    float *lastaccel, *lastvel, *lastpos;

    lastaccel = &_lastState._acceleration.x;
    lastvel = &_lastState._velocity.x;
    lastpos = &_lastState._displacement.x;

    // Begin Acceleration processing
    for(int i = 0; i < 3; i++)
    {
        // Converts sensor reading from mGs to m/s^2, then applies digital low pass filter to remove noise
        *accel = (*accel)*ACCEL_SCALE_FCTR*G_CONVERSION;
        *accel = *lastaccel + (*accel - *lastaccel)*ALPHA;

        // A heavier low pass filter is used in an attempt to remove the bias/drift from the sensor
        _biasFilter[i] = _biasFilter[i] + (*accel - _biasFilter[i])*HEAVY_ALPHA;
        *accel = *accel - _biasFilter[i];

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
            _accelCounter[i]++;
        }
        else
        {
            _accelCounter[i] = 0;
        }

        float adjustedAccel = *accel;

        if(_accelCounter[i] >= 33)
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
        std::lock_guard<std::mutex> guard(_access);
        _lastState = _currentState;
    }
}


State StateTracker::getCurrentState()
{
    std::lock_guard<std::mutex> guard(_access);
    return _lastState;
}
