/*
 * Gpio144.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: jpollard
 */

#include "Gpio144.h"
#include "utils/ErrorLogger.h"

Gpio144::Gpio144() :
    _value(_path)
{
}


Gpio144::~Gpio144()
{
}


void Gpio144::makeInput()
{
    ERROR_LOGGER.recordError("Tried to use Gpio144::makeInput");
    throw OperationNotSupported("Gpio144::makeInput");
}


void Gpio144::makeOutput()
{
    ERROR_LOGGER.recordError("Tried to use Gpio144::makeOutput");
    throw OperationNotSupported("Gpio144::makeOutput");
}


void Gpio144::setState(int state)
{
    std::lock_guard<std::mutex> guard(_lock);
    _value.write(state);
}


int Gpio144::readState()
{
    ERROR_LOGGER.recordError("Tried to use Gpio144::readState");
    throw OperationNotSupported("Gpio144::readState");
}
