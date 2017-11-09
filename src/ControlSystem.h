/*
 * ControlSystem.h
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#ifndef SRC_CONTROLSYSTEM_H_
#define SRC_CONTROLSYSTEM_H_

#include "Supervisor.h"
#include "AIEngine.h"
#include "PathPlanner.h"

class ControlSystem : public Supervisor
{
public:
    ControlSystem(std::shared_ptr<Vehicle> vehicle);
    virtual ~ControlSystem();

    void start();

private:
    AIEngine m_controller;
    PathPlanner m_planner;

};

#endif /* SRC_CONTROLSYSTEM_H_ */
