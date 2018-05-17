/*
 * SimulatedVehicle.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jpollard
 */

#ifndef SRC_SIMULATEDVEHICLE_H_
#define SRC_SIMULATEDVEHICLE_H_

#include "Vehicle.h"
#include "SimulationEngine.h"

class SimulatedVehicle : public Vehicle
{
public:
    SimulatedVehicle();
    virtual ~SimulatedVehicle();

    State getPose();
    int getNumberOfMotors() { return 2; }

    void runCommand(const VehicleCommand& command);

    void start() {};
    void stop() {};

private:
    SimulationEngine simulator;

};

#endif /* SRC_SIMULATEDVEHICLE_H_ */
