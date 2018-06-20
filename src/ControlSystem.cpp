/*
 * ControlSystem.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "ControlSystem.h"
#include "paths/SimplePath.h"

ControlSystem::ControlSystem(std::shared_ptr<Vehicle> vehicle) :
    Supervisor(vehicle),
    _learner(vehicle->getNumberOfMotors(), &_memories),
    _planner(new SimplePath()),
    _controller(&_memories)
{

}


ControlSystem::~ControlSystem()
{
}


void ControlSystem::start()
{
    startThread();
}


void ControlSystem::stop()
{
    // Stop the thread
}


void ControlSystem::threadRoutine()
{
    while(true)
    {
        if(!_learner.isLearningComplete())
            runMovement(&_learner);
        else
            runMovement(&_controller);

        usleep(2000000);
    }
}


void ControlSystem::runMovement(MovementController* controller)
{
    State currentState = _vehicle->getPose();
    _planner->updateTarget(currentState);
    State currentTarget = _planner->getTarget();

    VehicleCommand command = controller->getCommandToExecute(currentTarget, currentState);
    _vehicle->runCommand(command);

    State newState = _vehicle->getPose();
    controller->processCommandResults(newState);
}
