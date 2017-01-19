/*
 * GPIO.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "GPIO.h"
#include "ErrorHandler.h"

GPIO::GPIO()
{

}

GPIO::~GPIO()
{
	if(value.is_open())
		value.close();

	if(direction.is_open())
		direction.close();
}

void GPIO::Initialize(string gpionumber)
{
	location = "/sys/class/gpio/gpio" + gpionumber;
	value.open((location + "/value").c_str());
	direction.open((location + "/direction").c_str());

	if(!value.is_open())
		ErrorHandler::recorderror(Exception("failed to open " + location + "value file"));

	if(!direction.is_open())
		ErrorHandler::recorderror(Exception("failed to open " + location + "direction file"));
}

void GPIO::makeInput()
{
	direction << "in";
}

void GPIO::makeOutput()
{
	direction << "out";
}

void GPIO::setState(int state)
{
	if(state == 0)
		value << 0;
	else
		value << 1;
}

int GPIO::readState()
{
	//not implemented yet
	return -1;
}
