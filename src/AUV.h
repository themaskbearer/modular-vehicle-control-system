/*
 * AUV.h
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#ifndef SRC_AUV_H_
#define SRC_AUV_H_

#include <memory>

#include "vehicle/Vehicle.h"
#include "supervisor/Supervisor.h"

class AUV {
public:
    AUV();
    ~AUV();

    void run();
    void shutdown();

private:
    Vehicle::Ptr _vehicle;
    Supervisor::Ptr _supervisor;

};

#endif /* SRC_AUV_H_ */
