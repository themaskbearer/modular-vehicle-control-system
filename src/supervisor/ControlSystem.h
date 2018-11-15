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
#include "LearningBehavior.h"
#include "PathPlanner.h"
#include "vehicle/Vehicle.h"

class ControlSystem : public Supervisor, Thread
{
public:
    ControlSystem(Vehicle::Ptr vehicle);
    virtual ~ControlSystem();

    void start() override;
    void stop() override;

private:
    Vehicle::Ptr _vehicle;

    LearningBehavior _learner;
    PathPlanner _planner;
    AIEngine _controller;

    MemoryStorage _memories;

    void threadRoutine();
    void runMovement(MovementController* controller);
};

#endif /* SRC_CONTROLSYSTEM_H_ */
