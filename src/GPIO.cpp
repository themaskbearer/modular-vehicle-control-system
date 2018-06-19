/*
 * GPIO.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "GPIO.h"
#include "utils/ErrorHandler.h"
#include "thread/LockGuard.h"

#include <cstdlib>

GPIO::GPIO()
{
}


GPIO::GPIO(const GPIO& old)
{
}


GPIO::~GPIO()
{
    if(_value.is_open())
        _value.close();

    if(_direction.is_open())
        _direction.close();
}


void GPIO::initialize(std::string gpioNumber)
{
    LockGuard guard(_access);

    if(gpioNumber == "144")
        initialize144();
    else
    {
        _location = "/sys/class/gpio/gpio" + gpioNumber;
        _value.open((_location + "/value").c_str());

        _direction.open((_location + "/direction").c_str());

        if(!_value.is_open())
            ERROR_HANDLER->recordError(Exception("failed to open " + _location + " value file"));
        else if(!_direction.is_open())
            ERROR_HANDLER->recordError(Exception("failed to open " + _location + " direction file"));
        else
            _initialized = true;
    }
}


void GPIO::initialize144()
{
    _is144 = true;

    _location = "/sys/class/gpio/gpio";
    _location += "144";
    _value.open((_location + "/value").c_str());

    if(!_value.is_open())
        ERROR_HANDLER->recordError(Exception("failed to open " + _location + " value file"));
    else
        _initialized = true;
}


void GPIO::makeInput()
{
    if(_is144)
        return;

    LockGuard guard(_access);

    if(!_initialized)
        throw Exception("Gpio " + _location + " not intialized");

    std::string str = "echo in > ";
    str += _location;
    str += "/direction";
    system(str.c_str());
}


void GPIO::makeOutput()
{
    if(_is144)
        return;

    LockGuard guard(_access);

    if(!_initialized)
        throw Exception("Gpio " + _location + " not intialized");

    std::string str = "echo out > ";
    str += _location;
    str += "/direction";
    system(str.c_str());
}


void GPIO::setState(int state)
{
    LockGuard guard(_access);

    if(!_initialized)
        throw Exception("Gpio " + _location + " not intialized");

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


int GPIO::readState()
{
    //not implemented yet
    return -1;
}
