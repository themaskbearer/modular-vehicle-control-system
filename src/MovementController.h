/*
 * MovementController.h
 *
 *  Created on: May 17, 2018
 *      Author: jpollard
 */

#ifndef SRC_MOVEMENTCONTROLLER_H_
#define SRC_MOVEMENTCONTROLLER_H_

#include "VehicleCommand.h"
#include "State.h"
#include "Memory.h"
#include <vector>

typedef std::vector<Memory> MemoryStorage;

class MovementController
{
public:
    MovementController(MemoryStorage* memories) : m_memories(memories) {}
    virtual ~MovementController() {}

    virtual VehicleCommand getCommandToExecute(const State& currentTarget, const State& currentState) =0;
    virtual void processCommandResults(const State& finalState) =0;

protected:
    MemoryStorage* m_memories;
};

#endif /* SRC_MOVEMENTCONTROLLER_H_ */
