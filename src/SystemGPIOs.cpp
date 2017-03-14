/*
 * SystemGPIOs.cpp
 *
 * Created on: Sep 7, 2012
 *
Author: jpollard
 */


#include "SystemGPIOs.h"
#include "MotorConstants.h"

map<int, GPIO> SystemGPIOs::GPIOS;


SystemGPIOs::SystemGPIOs()
{
    GPIOS.clear();

    GPIOS.insert(pair<int, GPIO>(MOTOR1DIR, GPIO()));
    GPIOS.insert(pair<int, GPIO>(MOTOR1EN, GPIO()));
    GPIOS.insert(pair<int, GPIO>(MOTOR2DIR, GPIO()));
    GPIOS.insert(pair<int, GPIO>(MOTOR2EN, GPIO()));
    GPIOS.insert(pair<int, GPIO>(MOTOR3DIR, GPIO()));
    GPIOS.insert(pair<int, GPIO>(MOTOR3EN, GPIO()));

    GPIOS.find(MOTOR1DIR)->second.initialize("144");
    GPIOS.find(MOTOR1EN)->second.initialize("174");
    GPIOS.find(MOTOR2DIR)->second.initialize("173");
    GPIOS.find(MOTOR2EN)->second.initialize("175");
    GPIOS.find(MOTOR3DIR)->second.initialize("147");
    GPIOS.find(MOTOR3EN)->second.initialize("172");
}


SystemGPIOs::~SystemGPIOs()
{
}


GPIO* SystemGPIOs::getGPIO(int gpioNumber)
{
    map<int, GPIO>::iterator iter = GPIOS.find(gpioNumber);

    if(iter == GPIOS.end())
        return NULL;
    else
        return &(iter->second);
}
