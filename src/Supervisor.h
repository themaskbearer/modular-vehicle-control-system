/*
 * Supervisor.h
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#ifndef SRC_SUPERVISOR_H_
#define SRC_SUPERVISOR_H_

#include <memory>

#include "Vehicle.h"

class Supervisor {
public:
    Supervisor(std::shared_ptr<Vehicle> vehicle) : m_vehicle(vehicle) {}
    virtual ~Supervisor() {}

    virtual void start() =0;
    virtual void stop() =0;

protected:
    std::shared_ptr<Vehicle> m_vehicle;
};

#endif /* SRC_SUPERVISOR_H_ */
