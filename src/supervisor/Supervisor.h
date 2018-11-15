/*
 * Supervisor.h
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#ifndef SRC_SUPERVISOR_H_
#define SRC_SUPERVISOR_H_

#include <memory>

#include "vehicle/Vehicle.h"

class Supervisor {
public:
    Supervisor(std::shared_ptr<Vehicle> vehicle) : _vehicle(vehicle) {}
    virtual ~Supervisor() {}

    virtual void start() =0;
    virtual void stop() =0;

protected:
    std::shared_ptr<Vehicle> _vehicle;
};

#endif /* SRC_SUPERVISOR_H_ */
