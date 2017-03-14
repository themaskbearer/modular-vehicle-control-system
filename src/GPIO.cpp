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
    Initialized = false;
    is144 = false;

    int error = sem_init(&Access, 0, 1);
    if(error == -1)
        throw Exception("Failed to create semaphore for GPIO");
}


GPIO::GPIO(const GPIO& Old)
{
    Initialized = false;
    is144 = false;

    int error = sem_init(&Access, 0, 1);
    if(error == -1)
        throw Exception("Failed to create semaphore for GPIO");
}


GPIO::~GPIO()
{
    if(value.is_open())
        value.close();

    if(direction.is_open())
        direction.close();

    sem_destroy(&Access);
}


void GPIO::Initialize(string gpionumber)
{
    if(!sem_wait(&Access))
    {
        if(gpionumber == "144")
            Initialize144();
        else
        {
            location = "/sys/class/gpio/gpio" + gpionumber;
            value.open((location + "/value").c_str());

            direction.open((location + "/direction").c_str());

            if(!value.is_open())
                ErrorHandler::recorderror(Exception("failed to open " + location + " value file"));
            else if(!direction.is_open())
                ErrorHandler::recorderror(Exception("failed to open " + location + " direction file"));
            else
                Initialized = true;
        }

        sem_post(&Access);
    }
}


void GPIO::Initialize144()
{
    is144 = true;

    location = "/sys/class/gpio/gpio";
    location += "144";
    value.open((location + "/value").c_str());

    if(!value.is_open())
        ErrorHandler::recorderror(Exception("failed to open " + location + " value file"));
    else
        Initialized = true;
}


void GPIO::makeInput()
{
    if(is144)
        return;

    if(!sem_wait(&Access))
    {
        if(!Initialized)
            throw Exception("Gpio " + location + " not intialized");

        string str = "echo in > ";
        str += location;
        str += "/direction";
        system(str.c_str());

        sem_post(&Access);
    }
}


void GPIO::makeOutput()
{
    if(is144)
        return;

    if(!sem_wait(&Access))
    {
        if(!Initialized)
            throw Exception("Gpio " + location + " not intialized");

        string str = "echo out > ";
        str += location;
        str += "/direction";
        system(str.c_str());

        sem_post(&Access);
    }
}


void GPIO::setState(int state)
{
    if(!sem_wait(&Access))
    {
        if(!Initialized)
            throw Exception("Gpio " + location + " not intialized");

        if(state == 0)
        {
            string str = "echo 0 > ";
            str += location;
            str += "/value";
            system(str.c_str());
        }
        else
        {
            string str = "echo 1 > ";
            str += location;
            str += "/value";
            system(str.c_str());
        }

        sem_post(&Access);
    }
}


int GPIO::readState()
{
    //not implemented yet
    return -1;
}
