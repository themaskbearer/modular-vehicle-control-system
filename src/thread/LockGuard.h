/*
 * LockGuard.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jpollard
 */

#ifndef SRC_THREAD_LOCKGUARD_H_
#define SRC_THREAD_LOCKGUARD_H_

#include "Mutex.h"

class LockGuard
{
public:
    LockGuard(Mutex& mutex);
    virtual ~LockGuard();

private:
    Mutex& _mutex;

};

#endif /* SRC_THREAD_LOCKGUARD_H_ */
