/*
 * StateTracker.h
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#ifndef STATETRACKER_H_
#define STATETRACKER_H_

#include "semaphore.h"

#include <vector>
using std::vector;

#include "Thread.h"
#include "i2cHandler.h"
#include "Memory.h"
#include "DataLogger.h"

#define ACCEL_SCALE_FCTR        4
#define G_CONVERSION            9.81/1000

#define GYRO_SCALE_FCTR         0.069565217
#define GYROX_BIAS              -87.6620
#define GYROY_BIAS              18.2860
#define GYROZ_BIAS              -5.3140

#define GMAG                    236.33

#define ALPHA                   0.05
#define HEAVY_ALPHA             0.001
#define P                       100

#define RADIANS M_PI/180

#define DELTA_T 0.01


class StateTracker: public Thread
{
private:
    i2cHandler sensors;
    State CurrentState;
    State LastState;
    vector<float> R;
    int AccelCounter[3];
    float BiasFilter[3];

    sem_t Access;

    void ThreadRoutine();
    void initializeOrientation();

    vector<float> CreateRotationMatrix(float a, float b, float g);
    vector<float> MultiplyRMatrix(vector<float> R, vector<float> Rb);
    vector<float> MultiplyPosition(vector<float> R, vector<float> p);

    void updateState(sensordata data);

public:
    StateTracker();
    virtual ~StateTracker();

    State getCurrentState();
};

#endif /* STATETRACKER_H_ */
