/*
 * Mutex.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jpollard
 */

#ifndef SRC_THREAD_MUTEX_H_
#define SRC_THREAD_MUTEX_H_


#include <pthread.h>

class Mutex
{
public:
    Mutex();
    virtual ~Mutex();

    void lock();
    void unlock();

private:
    pthread_mutex_t m_mutex;

};

#endif /* SRC_THREAD_MUTEX_H_ */
