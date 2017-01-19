/*
 * Motor.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "Motor.h"

Motor::Motor(string directionIO, string enableIO)
{
	direction.Initialize(directionIO);
	enable.Initialize(enableIO);
}

Motor::~Motor()
{

}

void Motor::On()
{
	enable.setState(1);
}

void Motor::Off()
{
	enable.setState(0);
}

void Motor::Forward()
{
	direction.setState(1);
}

void Motor::Reverse()
{
	direction.setState(0);
}
