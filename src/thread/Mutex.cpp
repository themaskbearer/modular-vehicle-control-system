/*
 * Mutex.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: jpollard
 */

#include "utils/ErrorLogger.h"
#include "Mutex.h"
#include "utils/Exceptions.h"
#include "utils/OperatorFunctions.h"

Mutex::Mutex()
{
    int error = pthread_mutex_init(&_mutex, NULL);
    if(error)
        throw Exception("Failed to initialize mutex", errno);
}


Mutex::~Mutex()
{
    int error = pthread_mutex_destroy(&_mutex);
    if(error)
        ERROR_LOGGER.recordError("Failed to destroy mutex, err: " + errno);
}


void Mutex::lock()
{
    int error = pthread_mutex_lock(&_mutex);
    if(error)
        throw Exception("Failed to lock mutex", errno);
}


void Mutex::unlock()
{
    int error = pthread_mutex_unlock(&_mutex);
        if(error)
            throw Exception("Failed to unlock mutex", errno);
}
