/*
 * Vehicle.h
 *
 *  Created on: Sep 21, 2017
 *      Author: jpollard
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "State.h"
#include "VehicleCommand.h"

class Vehicle
{
public:
    Vehicle() {}
    virtual ~Vehicle() {};

    virtual State getPose() =0;
    virtual int getNumberOfMotors() =0;

    // Blocking command, runs on the Supervisor's thread
    virtual void runCommand(const VehicleCommand& command) =0;

    virtual void start() =0;
    virtual void stop() =0;
};

#endif /* VEHICLE_H_ */
