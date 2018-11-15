/*
 * Thread.h
 *
 *  Created on: Mar 3, 2012
 *      Author: jpollard
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <thread>
#include <atomic>


class Thread
{
public:
    Thread();
    virtual ~Thread();

    void start();
    void stop();

protected:
    bool isRunning() { return _running; }

private:
    std::atomic_bool _running;
    std::thread _thread;

    virtual void threadRoutine() =0;
};

#endif /* THREAD_H_ */
