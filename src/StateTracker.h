/*
 * StateTracker.h
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#ifndef STATETRACKER_H_
#define STATETRACKER_H_

#include "Thread.h"
#include "i2cHandler.h"
#include "Memory.h"
#include "DataLogger.h"

#define GRAVITY_SAMPLES 50

#define ALPHA 0.1

#define ACCEL_SCALE_FCTR 4
#define ACCEL_NOISE 3

#define GYRO_SCALE_FCTR 0.069565217
#define GYRO_X_BIAS 87.5
#define GYRO_Y_BIAS 21.5
#define GYRO_Z_BIAS 12
#define GYRO_NOISE 3

#define RADIANS M_PI/180

#define INTEGRATION_ERROR 15



class StateTracker: public Thread
{
private:
	i2cHandler sensors;
	State CurrentState;
	State LastState;
	sensordata LastData;

	float Gmag;

	int IntegratedAccelX;
	bool accelerating;
	bool decelerating;

	void ThreadRoutine();
	void initializeOrientation();
	void filterGyro(sensordata& data);
	void updateOrientation(sensordata data);
	void filterAccel(sensordata& data);
	void removeGravity(sensordata& data);
	void updatePosition(sensordata data);
	void MovementApproximator(sensordata data);
	void updateState(sensordata data);

public:
	StateTracker();
	virtual ~StateTracker();

	State getCurrentState();
};

#endif /* STATETRACKER_H_ */
