/*
 * ControlSystem.h
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#ifndef SRC_CONTROLSYSTEM_H_
#define SRC_CONTROLSYSTEM_H_

#include "Supervisor.h"
#include "MovementController.h"
#include "AIEngine.h"
#include "ConfigurationLearner.h"
#include "PathPlanner.h"

class ControlSystem : public Supervisor, Thread
{
public:
    ControlSystem(std::shared_ptr<Vehicle> vehicle);
    virtual ~ControlSystem();

    void start();
    void stop();

private:
    ConfigurationLearner _learner;
    PathPlanner _planner;
    AIEngine _controller;

    MemoryStorage _memories;

    void threadRoutine();
    void runMovement(MovementController* controller);
};

#endif /* SRC_CONTROLSYSTEM_H_ */
