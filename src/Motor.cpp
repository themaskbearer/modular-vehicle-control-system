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
    m_direction = SYSTEM_GPIOS->getGPIO(directionIO);
    m_enable = SYSTEM_GPIOS->getGPIO(enableIO);
}


Motor::Motor(const Motor &oldMotor)
{
    m_direction = oldMotor.m_direction;
    m_enable = oldMotor.m_enable;
}


Motor::~Motor()
{
}


void Motor::on()
{
    m_enable->setState(1);
}


void Motor::off()
{
    m_enable->setState(0);
}


void Motor::forward()
{
    m_direction->setState(1);
}


void Motor::reverse()
{
    m_direction->setState(0);
}
