/*
 * Gpio.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "Gpio.h"
#include "utils/ErrorLogger.h"
#include "utils/OperatorFunctions.h"


Gpio::Gpio(unsigned int gpioNumber) :
    _direction(_path + gpioNumber + "/direction"),
    _value(_path + gpioNumber + "/value")
{
}


Gpio::~Gpio()
{
}


void Gpio::makeInput()
{
    std::lock_guard<std::mutex> guard(_access);
    _direction.write("in");
}


void Gpio::makeOutput()
{
    std::lock_guard<std::mutex> guard(_access);
    _direction.write("out");
}


void Gpio::setState(int state)
{
	std::lock_guard<std::mutex> guard(_access);
	_value.write(state);
}


int Gpio::readState()
{
    ERROR_LOGGER.recordError("Tried to use Gpio::readState");
    throw OperationNotSupported("Gpio::readState");
}
