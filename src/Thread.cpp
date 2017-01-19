/*
 * Thread.cpp
 *
 *  Created on: Mar 3, 2012
 *      Author: jpollard
 */

#include "Thread.h"

#include "Exceptions.h"

Thread::Thread()
{

}

Thread::~Thread()
{
	pthread_cancel(thread);
}

void *Thread::ThreadLauncher(void* arg)
{
	reinterpret_cast<Thread*>(arg)->ThreadRoutine();
	return NULL;
}

void Thread::StartThread()
{
	int result = pthread_create(&thread, NULL, &ThreadLauncher, this);

	if(result)
		throw Exception("Could not launch thread", result);
}

void Thread::ThreadRoutine()
{

}
