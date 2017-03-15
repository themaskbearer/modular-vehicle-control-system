/*
 * LockGuard.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: jpollard
 */

#include "thread/LockGuard.h"

LockGuard::LockGuard(Mutex& mutex) :
        m_mutex(mutex)
{
    m_mutex.lock();
}

LockGuard::~LockGuard()
{
    m_mutex.unlock();
}

