/*
 * ControlSystem.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "ControlSystem.h"

ControlSystem::ControlSystem(std::shared_ptr<Vehicle> vehicle) :
    Supervisor(vehicle),
    m_learner(vehicle->getNumberOfMotors(), &m_memories),
    m_controller(&m_memories)
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
        if(!m_learner.isLearningComplete())
            runMovement(&m_learner);
        else
            runMovement(&m_controller);

        usleep(2000000);
    }
}


void ControlSystem::runMovement(MovementController* controller)
{
    State currentState = m_vehicle->getPose();
    m_planner.updateTarget(currentState);
    State currentTarget = m_planner.getTarget();

    VehicleCommand command = controller->getCommandToExecute(currentTarget, currentState);
    m_vehicle->runCommand(command);

    State newState = m_vehicle->getPose();
    controller->processCommandResults(newState);
}
