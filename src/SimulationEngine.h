/*
 * SimulationEngine.h
 *
 * * Created on: Nov 22, 2012
 * * Author: jpollard
 * */

#ifndef SIMULATIONENGINE_H_
#define SIMULATIONENGINE_H_

#include "State.h"
#include "VehicleCommand.h"

class SimulationEngine
{
public:
    SimulationEngine();
    virtual ~SimulationEngine();

    void makeMovement(const VehicleCommand& command);
    State getState();

private:
    State CurrentState;
};

#endif /* SIMULATIONENGINE_H_ */
