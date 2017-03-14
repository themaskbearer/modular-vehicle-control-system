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
    direction = SystemGPIOs::GetGPIO(directionIO);
    enable = SystemGPIOs::GetGPIO(enableIO);
}


Motor::Motor(const Motor &Oldmotor)
{
    direction = Oldmotor.direction;
    enable = Oldmotor.enable;
}


Motor::~Motor()
{
}


void Motor::On()
{
    enable->setState(1);
}


void Motor::Off()
{
    enable->setState(0);
}


void Motor::Forward()
{
    direction->setState(1);
}


void Motor::Reverse()
{
    direction->setState(0);
}
