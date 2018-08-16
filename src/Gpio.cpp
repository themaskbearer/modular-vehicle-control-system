/*
 * Gpio.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "utils/ErrorLogger.h"
#include "Gpio.h"
#include "thread/LockGuard.h"

#include <cstdlib>

Gpio::Gpio(unsigned int gpioNumber)
{
    if(gpioNumber == 144)
        initialize144();
    else
    {
        _location = "/sys/class/gpio/gpio" + gpioNumber;
        _value.open((_location + "/value").c_str());
        if(!_value.is_open()) {
            ERROR_LOGGER.recordError("failed to open " + _location + " value file");
            throw FileOpenFailure(_location + "/value");
        }

        _direction.open((_location + "/direction").c_str());
        if(!_direction.is_open()) {
            ERROR_LOGGER.recordError("failed to open " + _location + " direction file");
            throw FileOpenFailure(_location + "/direction");
        }
    }
}


void Gpio::initialize144()
{
    _is144 = true;

    _location = "/sys/class/gpio/gpio";
    _location += "144";
    _value.open((_location + "/value").c_str());

    if(!_value.is_open()) {
        ERROR_LOGGER.recordError("failed to open " + _location + " value file");
        throw FileOpenFailure(_location + "/value");
    }
}


Gpio::~Gpio()
{
    _value.close();
    _direction.close();
}


void Gpio::makeInput()
{
    // GPIO 144's direction is unable to be changed, so no-op
    if(_is144)
        return;

    LockGuard guard(_access);

    std::string str = "echo in > ";
    str += _location;
    str += "/direction";
    system(str.c_str());
}


void Gpio::makeOutput()
{
    // GPIO 144's direction is unable to be changed, so no-op
    if(_is144)
        return;

    LockGuard guard(_access);

    std::string str = "echo out > ";
    str += _location;
    str += "/direction";
    system(str.c_str());
}


void Gpio::setState(int state)
{
    LockGuard guard(_access);

    if(state == 0)
    {
        std::string str = "echo 0 > ";
        str += _location;
        str += "/value";
        system(str.c_str());
    }
    else
    {
        std::string str = "echo 1 > ";
        str += _location;
        str += "/value";
        system(str.c_str());
    }
}


int Gpio::readState()
{
    //not implemented yet
    return -1;
}
