/*
 * SystemGPIOs.cpp
 *
 * Created on: Sep 7, 2012
 *
Author: jpollard
 */


#include "SystemGPIOs.h"
#include "MotorConstants.h"


template<> SystemGPIOs::Ptr Singleton<SystemGPIOs>::_instance = nullptr;


SystemGPIOs::SystemGPIOs()
{
    GPIOS.insert(pair<int, GPIO::Ptr>(MOTOR1DIR, std::make_shared<GPIO>(144)));
    GPIOS.insert(pair<int, GPIO::Ptr>(MOTOR1EN,std::make_shared<GPIO>(174)));
    GPIOS.insert(pair<int, GPIO::Ptr>(MOTOR2DIR, std::make_shared<GPIO>(173)));
    GPIOS.insert(pair<int, GPIO::Ptr>(MOTOR2EN, std::make_shared<GPIO>(175)));
    GPIOS.insert(pair<int, GPIO::Ptr>(MOTOR3DIR, std::make_shared<GPIO>(147)));
    GPIOS.insert(pair<int, GPIO::Ptr>(MOTOR3EN, std::make_shared<GPIO>(172)));
}


SystemGPIOs::~SystemGPIOs()
{
}


GPIO::Ptr SystemGPIOs::getGPIO(int gpioNumber)
{
    auto iter = GPIOS.find(gpioNumber);

    if(iter == GPIOS.end())
        return NULL;
    else
        return iter->second;
}
