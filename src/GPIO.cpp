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
    if(m_value.is_open())
        m_value.close();

    if(m_direction.is_open())
        m_direction.close();
}


void GPIO::initialize(std::string gpioNumber)
{
    LockGuard guard(m_access);

    if(gpioNumber == "144")
        initialize144();
    else
    {
        m_location = "/sys/class/gpio/gpio" + gpioNumber;
        m_value.open((m_location + "/value").c_str());

        m_direction.open((m_location + "/direction").c_str());

        if(!m_value.is_open())
            ERROR_HANDLER->recordError(Exception("failed to open " + m_location + " value file"));
        else if(!m_direction.is_open())
            ERROR_HANDLER->recordError(Exception("failed to open " + m_location + " direction file"));
        else
            m_initialized = true;
    }
}


void GPIO::initialize144()
{
    m_is144 = true;

    m_location = "/sys/class/gpio/gpio";
    m_location += "144";
    m_value.open((m_location + "/value").c_str());

    if(!m_value.is_open())
        ERROR_HANDLER->recordError(Exception("failed to open " + m_location + " value file"));
    else
        m_initialized = true;
}


void GPIO::makeInput()
{
    if(m_is144)
        return;

    LockGuard guard(m_access);

    if(!m_initialized)
        throw Exception("Gpio " + m_location + " not intialized");

    std::string str = "echo in > ";
    str += m_location;
    str += "/direction";
    system(str.c_str());
}


void GPIO::makeOutput()
{
    if(m_is144)
        return;

    LockGuard guard(m_access);

    if(!m_initialized)
        throw Exception("Gpio " + m_location + " not intialized");

    std::string str = "echo out > ";
    str += m_location;
    str += "/direction";
    system(str.c_str());
}


void GPIO::setState(int state)
{
    LockGuard guard(m_access);

    if(!m_initialized)
        throw Exception("Gpio " + m_location + " not intialized");

    if(state == 0)
    {
        std::string str = "echo 0 > ";
        str += m_location;
        str += "/value";
        system(str.c_str());
    }
    else
    {
        std::string str = "echo 1 > ";
        str += m_location;
        str += "/value";
        system(str.c_str());
    }
}


int GPIO::readState()
{
    //not implemented yet
    return -1;
}
