/*
 * StateTracker.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#include "StateTracker.h"
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

    int error = sem_init(&m_access, 0, 1);
    if(error == -1)
        throw Exception("Failed to create semaphore for StateTracker");
}


StateTracker::~StateTracker()
{
    sem_destroy(&m_access);
}


void StateTracker::threadRoutine()
{
    initializeOrientation();

    while(true)
    {
        SensorData readings = m_sensors.getSensorData();
        updateState(readings);

        usleep(7100);
    }
}


void StateTracker::initializeOrientation()
{
    SensorData Initial = m_sensors.getSensorData();

    float g = atan2((float)Initial.Accelerometer.Y, (float)Initial.Accelerometer.Z);
    float b = asin(-(float)Initial.Accelerometer.X/GMAG);
    float a = 0;

    vector<float> temp = createRotationMatrix(a, b, g);
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

    float a = m_currentState.m_angVelocity.yaw*DELTA_T;
    float b = m_currentState.m_angVelocity.roll*DELTA_T;
    float g = m_currentState.m_angVelocity.pitch*DELTA_T;

    vector<float> temp = createRotationMatrix(a, b, g);
    m_R = multiplyRMatrix(m_R, temp);

    float xg = m_R[6]*GMAG;
    float yg = m_R[7]*GMAG;
    float zg = m_R[8]*GMAG;

    m_currentState.m_acceleration.x = data.Accelerometer.X - xg;
    m_currentState.m_acceleration.y = data.Accelerometer.Y - yg;
    m_currentState.m_acceleration.z = data.Accelerometer.Z - zg;

    vector<float> p(3, 0);

    p[0] = m_currentState.m_acceleration.x;
    p[1] = m_currentState.m_acceleration.y;
    p[2] = m_currentState.m_acceleration.z;

    p = multiplyPosition(m_R, p);

    m_currentState.m_acceleration.x = p[0];
    m_currentState.m_acceleration.y = p[1];
    m_currentState.m_acceleration.z = p[2];

    m_currentState.m_angPosition.roll = atan2(-m_R[6], sqrt(pow(m_R[0],2) + pow(m_R[3],2)));
    m_currentState.m_angPosition.yaw = atan2(m_R[3]/cos(m_currentState.m_angPosition.roll), m_R[0]/cos(m_currentState.m_angPosition.roll));
    m_currentState.m_angPosition.pitch = atan2(m_R[7]/cos(m_currentState.m_angPosition.roll), m_R[8]/cos(m_currentState.m_angPosition.roll));

    float *accel, *vel, *pos;

    accel = &m_currentState.m_acceleration.x;
    vel = &m_currentState.m_velocity.x;
    pos = &m_currentState.m_displacement.x;

    float *lastaccel, *lastvel, *lastpos;

    lastaccel = &m_lastState.m_acceleration.x;
    lastvel = &m_lastState.m_velocity.x;
    lastpos = &m_lastState.m_displacement.x;

    //Begin Acceleration processing

    for(int i = 0; i < 3; i++)
    {
        *accel = (*accel)*ACCEL_SCALE_FCTR*G_CONVERSION;
        *accel = *lastaccel + (*accel - *lastaccel)*ALPHA;

        m_biasFilter[i] = m_biasFilter[i] + (*accel - m_biasFilter[i])*HEAVY_ALPHA;
        *accel = *accel - m_biasFilter[i];

        if((*accel - *lastaccel) < 0.05 )
        {
            m_accelCounter[i]++;
        }
        else
        {
            m_accelCounter[i] = 0;
        }

        float adjaccel = *accel;

        if(m_accelCounter[i] >= 33)
        {
            float error = (-(*lastvel));
            adjaccel = error*P;
        }

        *vel = *lastvel + adjaccel*DELTA_T;
        *pos = *lastpos + (*vel)*DELTA_T;

        accel++;
        vel++;
        pos++;

        lastaccel++;
        lastvel++;
        lastpos++;
    }

    if(!sem_wait(&m_access))
    {
        m_lastState = m_currentState;
        sem_post(&m_access);
    }
}


vector<float> StateTracker::createRotationMatrix(float a, float b, float g)
{
    vector<float> R;

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


vector<float> StateTracker::multiplyRMatrix(vector<float> R, vector<float> Rb)
{
    vector<float> ReturnedMatrix(9, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                ReturnedMatrix[i*3 + j] += R[i*3 + k] * Rb[j + k*3];

    return ReturnedMatrix;
}


vector<float> StateTracker::multiplyPosition(vector<float> R, vector<float> p)
{
    vector<float> ReturnedMatrix(3, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ReturnedMatrix[i] += R[i*3 + j] * p[j];

    return ReturnedMatrix;
}


State StateTracker::getCurrentState()
{
    State ReturnedState;

    if(!sem_wait(&m_access))
    {
        ReturnedState = m_lastState;
        sem_post(&m_access);
    }

    return ReturnedState;
}
