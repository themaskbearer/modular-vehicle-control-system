/*
 * AIEngine.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef AIENGINE_H_
#define AIENGINE_H_

#include "thread/Thread.h"
#include "MovementController.h"
#include "Memory.h"
#include <vector>

class AIEngine : public MovementController
{
public:
    AIEngine(MemoryStorage* memories);
    virtual ~AIEngine();

    VehicleCommand getCommandToExecute(const State& currentTarget, const State& currentState);
    void processCommandResults(const State& finalState);

private:
    State _currentMoveInitialState;
    State _currentMovePrediction;
    Memory* _currentActingMemory = nullptr;

    Memory* getBestMemory(const State& Target);

    float compareStates(const State& state1, const State& state2);

    void logState(const std::string& title, const State& state);
};

#endif /* AIENGINE_H_ */
