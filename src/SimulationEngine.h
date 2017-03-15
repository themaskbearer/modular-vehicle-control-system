/*
 * SimulationEngine.h
 *
 * * Created on: Nov 22, 2012
 * * Author: jpollard
 * */

#ifndef SIMULATIONENGINE_H_
#define SIMULATIONENGINE_H_

#include "Memory.h"

class SimulationEngine
{
public:
    SimulationEngine();
    virtual ~SimulationEngine();

    State makeMovement(Memory memToMove);
    State getInitialState();

private:
    State CurrentState;
};

#endif /* SIMULATIONENGINE_H_ */
