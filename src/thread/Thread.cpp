/*
 * Thread.cpp
 *
 *  Created on: Mar 3, 2012
 *      Author: jpollard
 */

#include "Thread.h"

#include "utils/Exceptions.h"

Thread::Thread() : _thread(-1)
{

}

Thread::~Thread()
{
    pthread_cancel(_thread);
}

void *Thread::threadLauncher(void* arg)
{
    reinterpret_cast<Thread*>(arg)->threadRoutine();
    return NULL;
}

void Thread::startThread()
{
    int result = pthread_create(&_thread, NULL, &threadLauncher, this);

    if(result)
        throw Exception("Could not launch _thread", result);
}
