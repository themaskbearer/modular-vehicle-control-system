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
        private:
                State CurrentState;
        public:
                SimulationEngine();
                virtual ~SimulationEngine();
                State MakeMovement(Memory MemToMove);
                State GetInitialState();
};

#endif /* SIMULATIONENGINE_H_ */
