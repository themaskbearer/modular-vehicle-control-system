/*
 * Motor.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "Motor.h"
#include "SystemGPIOs.h"


Motor::Motor(int directionIO, int enableIO)
{
    _direction = SYSTEM_GPIOS->getGPIO(directionIO);
    _enable = SYSTEM_GPIOS->getGPIO(enableIO);
}


Motor::Motor(const Motor &oldMotor)
{
    _direction = oldMotor._direction;
    _enable = oldMotor._enable;
}


Motor::~Motor()
{
}


void Motor::on()
{
    _enable->setState(1);
}


void Motor::off()
{
    _enable->setState(0);
}


void Motor::forward()
{
    _direction->setState(1);
}


void Motor::reverse()
{
    _direction->setState(0);
}
