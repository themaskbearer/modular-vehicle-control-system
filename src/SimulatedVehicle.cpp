/*
 * SimulatedVehicle.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jpollard
 */

#include "SimulatedVehicle.h"


State SimulatedVehicle::getPose()
{
    return simulator.getState();
}


void SimulatedVehicle::runCommand(const VehicleCommand& command)
{
    simulator.makeMovement(command);
}
