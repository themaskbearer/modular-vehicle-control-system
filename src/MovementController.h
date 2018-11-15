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


class MovementController
{
public:
    virtual ~MovementController() = default;

    virtual VehicleCommand getCommandToExecute(const State& currentTarget, const State& currentState) =0;
    virtual void processCommandResults(const State& finalState) =0;
};

#endif /* SRC_MOVEMENTCONTROLLER_H_ */
