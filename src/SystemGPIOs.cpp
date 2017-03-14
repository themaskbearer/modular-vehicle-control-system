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

    GPIOS.find(MOTOR1DIR)->second.Initialize("144");
    GPIOS.find(MOTOR1EN)->second.Initialize("174");
    GPIOS.find(MOTOR2DIR)->second.Initialize("173");
    GPIOS.find(MOTOR2EN)->second.Initialize("175");
    GPIOS.find(MOTOR3DIR)->second.Initialize("147");
    GPIOS.find(MOTOR3EN)->second.Initialize("172");
}


SystemGPIOs::~SystemGPIOs()
{
    // TODO Auto-generated destructor stub
}


GPIO* SystemGPIOs::GetGPIO(int GPIONumber)
{
    map<int, GPIO>::iterator iter = GPIOS.find(GPIONumber);

    if(iter == GPIOS.end())
        return NULL;
    else
        return &(iter->second);
}
