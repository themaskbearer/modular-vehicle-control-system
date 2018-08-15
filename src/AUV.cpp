/*
 * AUV.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "AUV.h"
#include "SimulatedVehicle.h"
#include "ControlSystem.h"



AUV::AUV()
{
    // TODO: add switch depending on configuration which vehicle to use
    _vehicle = std::make_shared<SimulatedVehicle>();
    _supervisor.reset(new ControlSystem(_vehicle));
}


AUV::~AUV()
{

}


void AUV::run()
{
    _vehicle->start();
    _supervisor->start();

    while(true)
        usleep(1000000);
}


void AUV::shutdown()
{

}
