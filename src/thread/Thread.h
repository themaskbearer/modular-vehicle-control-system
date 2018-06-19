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
public:
    Thread();
    virtual ~Thread();

    void startThread();

private:
    pthread_t _thread;

    static void *threadLauncher(void *arg);
    virtual void threadRoutine() =0;
};

#endif /* THREAD_H_ */
