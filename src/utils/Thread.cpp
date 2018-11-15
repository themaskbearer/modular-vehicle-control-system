/*
 * Thread.cpp
 *
 *  Created on: Mar 3, 2012
 *      Author: jpollard
 */

#include "Thread.h"


Thread::Thread() :
    _running(false)
{
}

Thread::~Thread()
{
    if(_running) {
        _running = false;
        _thread.join();
    }
}


void Thread::start()
{
    if(!_running) {
        _running = true;
        _thread = std::thread(&Thread::threadRoutine, this);
    }
}


void Thread::stop()
{
    if(_running) {
        _running = false;
        _thread.join();
    }
}
