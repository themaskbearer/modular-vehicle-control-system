/*
 * Supervisor.h
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#ifndef SRC_SUPERVISOR_H_
#define SRC_SUPERVISOR_H_

#include <memory>

class Supervisor
{
public:
    typedef std::unique_ptr<Supervisor> Ptr;

    virtual ~Supervisor() = default;

    virtual void start() =0;
    virtual void stop() =0;
};

#endif /* SRC_SUPERVISOR_H_ */
