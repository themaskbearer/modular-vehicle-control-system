/*
 * StateTracker.h
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#ifndef STATETRACKER_H_
#define STATETRACKER_H_

#include <vector>
#include <mutex>

#include "thread/Thread.h"
#include "i2cHandler.h"
#include "Memory.h"
#include "utils/DataLogger.h"

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
public:
    StateTracker();
    virtual ~StateTracker();

    State getCurrentState();

private:
    I2cHandler _sensors;
    State _currentState;
    State _lastState;
    std::vector<float> _R;
    int _accelCounter[3];
    float _biasFilter[3];

    std::mutex _access;

    void threadRoutine();
    void initializeOrientation();

    void updateState(SensorData data);
};

#endif /* STATETRACKER_H_ */
