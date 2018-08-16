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
    GPIOS.insert(pair<int, Gpio::Ptr>(MOTOR1DIR, std::make_shared<Gpio>(144)));
    GPIOS.insert(pair<int, Gpio::Ptr>(MOTOR1EN,std::make_shared<Gpio>(174)));
    GPIOS.insert(pair<int, Gpio::Ptr>(MOTOR2DIR, std::make_shared<Gpio>(173)));
    GPIOS.insert(pair<int, Gpio::Ptr>(MOTOR2EN, std::make_shared<Gpio>(175)));
    GPIOS.insert(pair<int, Gpio::Ptr>(MOTOR3DIR, std::make_shared<Gpio>(147)));
    GPIOS.insert(pair<int, Gpio::Ptr>(MOTOR3EN, std::make_shared<Gpio>(172)));
}


SystemGPIOs::~SystemGPIOs()
{
}


Gpio::Ptr SystemGPIOs::getGPIO(int gpioNumber)
{
    auto iter = GPIOS.find(gpioNumber);

    if(iter == GPIOS.end())
        return NULL;
    else
        return iter->second;
}
