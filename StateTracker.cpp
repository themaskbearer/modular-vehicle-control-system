/*
 * StateTracker.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: jpollard
 */

#include "StateTracker.h"
#include <cmath>

#define _USE_MATH_DEFINES
using std::tan;
using std::atan2;
using std::pow;

StateTracker::StateTracker()
{
	Gmag = 0;
	CurrentState = LastState = getEmptyState();

	IntegratedAccelX = 0;
	accelerating = false;
	decelerating = false;

	LastData.Gyro.X = 0;
	LastData.Gyro.Y = 0;
	LastData.Gyro.Z = 0;

	LastData.Accelerometer.X = 0;
	LastData.Accelerometer.Y = 0;
	LastData.Accelerometer.Z = 0;
}

StateTracker::~StateTracker()
{

}

void StateTracker::ThreadRoutine()
{
	initializeOrientation();

	while(true)
	{
		sensordata readings = sensors.getSensorData();
		updateState(readings);

		usleep(10000);
	}
}

void StateTracker::initializeOrientation()
{

	for(int i = 0; i < GRAVITY_SAMPLES; i++)
	{
		sensordata initialreading = sensors.getSensorData();

		float x = initialreading.Accelerometer.X;
		float y = initialreading.Accelerometer.Y;
		float z = initialreading.Accelerometer.Z;

		Gmag += std::sqrt(x*x + y*y +z*z);

		CurrentState.HPR.heading += atan2(y, x);
		CurrentState.HPR.roll += atan2(z, y);
		CurrentState.HPR.pitch += atan2(z, x);
	}

	Gmag /= GRAVITY_SAMPLES;
	CurrentState.HPR.heading /= GRAVITY_SAMPLES;
	CurrentState.HPR.roll /= GRAVITY_SAMPLES;
	CurrentState.HPR.pitch /= GRAVITY_SAMPLES;

	//Add functionality to gain initial rotation speeds as well
}

void StateTracker::updateState(sensordata data)
{
	LastState = CurrentState;

	filterGyro(data);
	updateOrientation(data);
	filterAccel(data);
	updatePosition(data);

	LastData = data;
}

void StateTracker::filterGyro(sensordata& data)
{
	data.Gyro.X -= GYRO_X_BIAS;
	data.Gyro.Y -= GYRO_Y_BIAS;
	data.Gyro.Z -= GYRO_Z_BIAS;

	data.Gyro.X = LastData.Gyro.X + ALPHA*(data.Gyro.X - LastData.Gyro.X);
	data.Gyro.Y = LastData.Gyro.Y + ALPHA*(data.Gyro.Y - LastData.Gyro.Y);
	data.Gyro.Z = LastData.Gyro.Z + ALPHA*(data.Gyro.Z - LastData.Gyro.Z);
}

void StateTracker::updateOrientation(sensordata data)
{
	CurrentState.HPR.roll = LastState.HPR.roll + data.Gyro.X*.01*GYRO_SCALE_FCTR*RADIANS;
	CurrentState.HPR.pitch = LastState.HPR.pitch + data.Gyro.Y*.01*GYRO_SCALE_FCTR*RADIANS;
	CurrentState.HPR.heading = LastState.HPR.heading + data.Gyro.Z*.01*GYRO_SCALE_FCTR*RADIANS;
}

void StateTracker::filterAccel(sensordata& data)
{
	removeGravity(data);

	data.Accelerometer.X = LastData.Accelerometer.X + ALPHA*(data.Accelerometer.X - LastData.Accelerometer.X);
	data.Accelerometer.Y = LastData.Accelerometer.Y + ALPHA*(data.Accelerometer.Y - LastData.Accelerometer.Y);
	data.Accelerometer.Z = LastData.Accelerometer.Z + ALPHA*(data.Accelerometer.Z - LastData.Accelerometer.Z);
}

void StateTracker::removeGravity(sensordata& data)
{
	float Xg = sqrt(Gmag*Gmag/(1 + pow(tan(CurrentState.HPR.heading), 2) + pow(tan(CurrentState.HPR.pitch), 2)));
	float Yg = Xg*tan(CurrentState.HPR.heading);
	float Zg = Xg*tan(CurrentState.HPR.pitch);

	data.Accelerometer.X -= Xg;
	data.Accelerometer.Y -= Yg;
	data.Accelerometer.Z -= Zg;
}

void StateTracker::updatePosition(sensordata data)
{
	CurrentState.Acceleration.x = data.Accelerometer.X*ACCEL_SCALE_FCTR;
	CurrentState.Velocity.x = LastState.Velocity.x + CurrentState.Acceleration.x * .01*ACCEL_SCALE_FCTR;
	CurrentState.Displacement.x = LastState.Displacement.x + CurrentState.Velocity.x * .01*ACCEL_SCALE_FCTR;

	MovementApproximator(data);
}

void StateTracker::MovementApproximator(sensordata data)
{
	IntegratedAccelX += data.Accelerometer.X;

	string msg = "Integrated Accel: ";
	msg = msg + IntegratedAccelX;
	DataLogger::recorddata(msg);

	if(data.Accelerometer.X > 0)
		accelerating = true;
	else if(data.Accelerometer.X < 0)
		decelerating = true;

	if(accelerating && decelerating && std::abs((float) IntegratedAccelX) < INTEGRATION_ERROR)
	{
		CurrentState.Velocity.x = 0;
		IntegratedAccelX = 0;

		accelerating = false;
		decelerating = false;

		msg = "return to zero speed!";
		DataLogger::recorddata(msg);
	}
}

State StateTracker::getCurrentState()
{
	return CurrentState;
}
