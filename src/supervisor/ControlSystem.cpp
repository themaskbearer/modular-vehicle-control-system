/*
 * ControlSystem.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "ControlSystem.h"

ControlSystem::ControlSystem(Vehicle::Ptr vehicle) :
    _vehicle(vehicle),
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

        std::this_thread::sleep_for(std::chrono::seconds(2));
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
