/*
 * Thread.cpp
 *
 *  Created on: Mar 3, 2012
 *      Author: jpollard
 */

#include "Thread.h"

#include "utils/Exceptions.h"

Thread::Thread() : m_thread(-1)
{

}

Thread::~Thread()
{
    pthread_cancel(m_thread);
}

void *Thread::threadLauncher(void* arg)
{
    reinterpret_cast<Thread*>(arg)->threadRoutine();
    return NULL;
}

void Thread::startThread()
{
    int result = pthread_create(&m_thread, NULL, &threadLauncher, this);

    if(result)
        throw Exception("Could not launch m_thread", result);
}
