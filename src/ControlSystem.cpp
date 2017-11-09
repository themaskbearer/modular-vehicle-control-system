/*
 * ControlSystem.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "ControlSystem.h"

ControlSystem::ControlSystem(std::shared_ptr<Vehicle> vehicle) :
    Supervisor(vehicle)
{


}

ControlSystem::~ControlSystem()
{

}


void ControlSystem::start()
{

}
