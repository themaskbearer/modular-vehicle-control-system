/*
 * ControlSystem.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "ControlSystem.h"

ControlSystem::ControlSystem(std::shared_ptr<Vehicle> vehicle) :
    Supervisor(vehicle),
    _learner(vehicle->getNumberOfMotors(), &_memories),
    _controller(&_memories)
{
}


ControlSystem::~ControlSystem()
{
}


void ControlSystem::start()
{
    Thread::start();
}


void ControlSystem::stop()
{
    Thread::stop();
}


void ControlSystem::threadRoutine()
{
    while(isRunning())
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
    _planner.updateTarget(currentState);
    State currentTarget = _planner.getTarget();

    VehicleCommand command = controller->getCommandToExecute(currentTarget, currentState);
    _vehicle->runCommand(command);

    State newState = _vehicle->getPose();
    controller->processCommandResults(newState);
}
