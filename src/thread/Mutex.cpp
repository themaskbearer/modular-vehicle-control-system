/*
 * Mutex.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: jpollard
 */

#include "Mutex.h"
#include "utils/Exceptions.h"
#include "utils/ErrorHandler.h"

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
        ERROR_HANDLER.recordError(Exception("Failed to destroy mutex", errno));
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
