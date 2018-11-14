/*
 * SystemGPIOs.cpp
 *
 * Created on: Sep 7, 2012
 *
Author: jpollard
 */


#include "SystemGPIOs.h"
#include "MotorConstants.h"
#include "Gpio.h"
#include "Gpio144.h"


template<> SystemGPIOs::Ptr Singleton<SystemGPIOs>::_instance = nullptr;


SystemGPIOs::SystemGPIOs()
{
    GPIOS.insert(pair<int, HardwareIO::Ptr>(MOTOR1DIR, std::make_shared<Gpio144>()));
    GPIOS.insert(pair<int, HardwareIO::Ptr>(MOTOR1EN,std::make_shared<Gpio>(174)));
    GPIOS.insert(pair<int, HardwareIO::Ptr>(MOTOR2DIR, std::make_shared<Gpio>(173)));
    GPIOS.insert(pair<int, HardwareIO::Ptr>(MOTOR2EN, std::make_shared<Gpio>(175)));
    GPIOS.insert(pair<int, HardwareIO::Ptr>(MOTOR3DIR, std::make_shared<Gpio>(147)));
    GPIOS.insert(pair<int, HardwareIO::Ptr>(MOTOR3EN, std::make_shared<Gpio>(172)));
}


SystemGPIOs::~SystemGPIOs()
{
}


HardwareIO::Ptr SystemGPIOs::getGPIO(int gpioNumber)
{
    auto iter = GPIOS.find(gpioNumber);

    if(iter == GPIOS.end())
        return nullptr;
    else
        return iter->second;
}
