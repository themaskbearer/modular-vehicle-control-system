/*
 * Thread.h
 *
 *  Created on: Mar 3, 2012
 *      Author: jpollard
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <unistd.h>

class Thread
{
private:
	pthread_t thread;

	static void *ThreadLauncher(void *arg);
	virtual void ThreadRoutine();

public:
	Thread();
	virtual ~Thread();

	void StartThread();
};

#endif /* THREAD_H_ */
