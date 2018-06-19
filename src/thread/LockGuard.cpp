/*
 * LockGuard.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: jpollard
 */

#include "thread/LockGuard.h"

LockGuard::LockGuard(Mutex& mutex) :
        _mutex(mutex)
{
    _mutex.lock();
}

LockGuard::~LockGuard()
{
    _mutex.unlock();
}

