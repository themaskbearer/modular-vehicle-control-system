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
    CurrentState = LastState = getEmptyState();

    R.push_back(1);
    R.push_back(0);
    R.push_back(0);

    R.push_back(0);
    R.push_back(1);
    R.push_back(0);

    R.push_back(0);
    R.push_back(0);
    R.push_back(1);

    for(int i = 0; i < 3; i++)
    {
        AccelCounter[i] = 0;
        BiasFilter[i] = 0;
    }

    int error = sem_init(&Access, 0, 1);
    if(error == -1)
        throw Exception("Failed to create semaphore for StateTracker");
}


StateTracker::~StateTracker()
{
    sem_destroy(&Access);
}


void StateTracker::ThreadRoutine()
{
    initializeOrientation();

    while(true)
    {
        sensordata readings = sensors.getSensorData();
        updateState(readings);

        usleep(7100);
    }
}


void StateTracker::initializeOrientation()
{
    sensordata Initial = sensors.getSensorData();

    float g = atan2((float)Initial.Accelerometer.Y, (float)Initial.Accelerometer.Z);
    float b = asin(-(float)Initial.Accelerometer.X/GMAG);
    float a = 0;

    vector<float> temp = CreateRotationMatrix(a, b, g);
    R = MultiplyRMatrix(R, temp);

//    CurrentState.RPY.pitch = g;
//    CurrentState.RPY.roll = b;
//    if(!sem_wait(&Access))
//    {
//        LastState = CurrentState;
//        sem_post(&Access);
//    }

    //Add functionality to gain initial rotation speeds as well
}


void StateTracker::updateState(sensordata data)
{
    CurrentState.AngVelocity.roll = (data.Gyro.Y - GYROY_BIAS)*GYRO_SCALE_FCTR*RADIANS;
    CurrentState.AngVelocity.pitch = (data.Gyro.X - GYROX_BIAS)*GYRO_SCALE_FCTR*RADIANS;
    CurrentState.AngVelocity.yaw = (data.Gyro.Z - GYROZ_BIAS)*GYRO_SCALE_FCTR*RADIANS;

    float a = CurrentState.AngVelocity.yaw*DELTA_T;
    float b = CurrentState.AngVelocity.roll*DELTA_T;
    float g = CurrentState.AngVelocity.pitch*DELTA_T;

    vector<float> temp = CreateRotationMatrix(a, b, g);
    R = MultiplyRMatrix(R, temp);

    float xg = R[6]*GMAG;
    float yg = R[7]*GMAG;
    float zg = R[8]*GMAG;

    CurrentState.Acceleration.x = data.Accelerometer.X - xg;
    CurrentState.Acceleration.y = data.Accelerometer.Y - yg;
    CurrentState.Acceleration.z = data.Accelerometer.Z - zg;

    vector<float> p(3, 0);

    p[0] = CurrentState.Acceleration.x;
    p[1] = CurrentState.Acceleration.y;
    p[2] = CurrentState.Acceleration.z;

    p = MultiplyPosition(R, p);

    CurrentState.Acceleration.x = p[0];
    CurrentState.Acceleration.y = p[1];
    CurrentState.Acceleration.z = p[2];

    CurrentState.RPY.roll = atan2(-R[6], sqrt(pow(R[0],2) + pow(R[3],2)));
    CurrentState.RPY.yaw = atan2(R[3]/cos(CurrentState.RPY.roll), R[0]/cos(CurrentState.RPY.roll));
    CurrentState.RPY.pitch = atan2(R[7]/cos(CurrentState.RPY.roll), R[8]/cos(CurrentState.RPY.roll));

    float *accel, *vel, *pos;

    accel = &CurrentState.Acceleration.x;
    vel = &CurrentState.Velocity.x;
    pos = &CurrentState.Displacement.x;

    float *lastaccel, *lastvel, *lastpos;

    lastaccel = &LastState.Acceleration.x;
    lastvel = &LastState.Velocity.x;
    lastpos = &LastState.Displacement.x;

    //Begin Acceleration processing

    for(int i = 0; i < 3; i++)
    {
        *accel = (*accel)*ACCEL_SCALE_FCTR*G_CONVERSION;
        *accel = *lastaccel + (*accel - *lastaccel)*ALPHA;

        BiasFilter[i] = BiasFilter[i] + (*accel - BiasFilter[i])*HEAVY_ALPHA;
        *accel = *accel - BiasFilter[i];

        if((*accel - *lastaccel) < 0.05 )
        {
            AccelCounter[i]++;
        }
        else
        {
            AccelCounter[i] = 0;
        }

        float adjaccel = *accel;

        if(AccelCounter[i] >= 33)
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

    if(!sem_wait(&Access))
    {
        LastState = CurrentState;
        sem_post(&Access);
    }
}


vector<float> StateTracker::CreateRotationMatrix(float a, float b, float g)
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


vector<float> StateTracker::MultiplyRMatrix(vector<float> R, vector<float> Rb)
{
    vector<float> ReturnedMatrix(9, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                ReturnedMatrix[i*3 + j] += R[i*3 + k] * Rb[j + k*3];

    return ReturnedMatrix;
}


vector<float> StateTracker::MultiplyPosition(vector<float> R, vector<float> p)
{
    vector<float> ReturnedMatrix(3, 0);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ReturnedMatrix[i] += R[i*3 + j] * p[j];

    return ReturnedMatrix;
}


State StateTracker::getCurrentState()
{
    State ReturnedState = getEmptyState();

    if(!sem_wait(&Access))
    {
        ReturnedState = LastState;
        sem_post(&Access);
    }

    return ReturnedState;
}
