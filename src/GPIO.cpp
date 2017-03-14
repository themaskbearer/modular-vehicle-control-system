/*
 * GPIO.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#include "GPIO.h"
#include "ErrorHandler.h"
#include <cstdlib>

GPIO::GPIO()
{
    m_initialized = false;
    m_is144 = false;

    int error = sem_init(&m_access, 0, 1);
    if(error == -1)
        throw Exception("Failed to create semaphore for GPIO");
}


GPIO::GPIO(const GPIO& old)
{
    m_initialized = false;
    m_is144 = false;

    int error = sem_init(&m_access, 0, 1);
    if(error == -1)
        throw Exception("Failed to create semaphore for GPIO");
}


GPIO::~GPIO()
{
    if(m_value.is_open())
        m_value.close();

    if(m_direction.is_open())
        m_direction.close();

    sem_destroy(&m_access);
}


void GPIO::initialize(std::string gpioNumber)
{
    if(!sem_wait(&m_access))
    {
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

        sem_post(&m_access);
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

    if(!sem_wait(&m_access))
    {
        if(!m_initialized)
            throw Exception("Gpio " + m_location + " not intialized");

        std::string str = "echo in > ";
        str += m_location;
        str += "/direction";
        system(str.c_str());

        sem_post(&m_access);
    }
}


void GPIO::makeOutput()
{
    if(m_is144)
        return;

    if(!sem_wait(&m_access))
    {
        if(!m_initialized)
            throw Exception("Gpio " + m_location + " not intialized");

        std::string str = "echo out > ";
        str += m_location;
        str += "/direction";
        system(str.c_str());

        sem_post(&m_access);
    }
}


void GPIO::setState(int state)
{
    if(!sem_wait(&m_access))
    {
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

        sem_post(&m_access);
    }
}


int GPIO::readState()
{
    //not implemented yet
    return -1;
}
