/*
 * AUV.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "AUV.h"
#include "SimulatedVehicle.h"
#include "ControlSystem.h"
#include "utils/DataLogger.h"
#include "utils/ErrorHandler.h"



AUV::AUV()
{

}


AUV::~AUV()
{

}


void AUV::initialize()
{
    ERROR_HANDLER->initialize("errors.log");
    ERROR_HANDLER->startThread();

    DATA_LOGGER->initialize();
    DATA_LOGGER->startThread();

    // TODO: add switch depending on configuration which vehicle to use
    _vehicle.reset(new SimulatedVehicle());
    _supervisor.reset(new ControlSystem(_vehicle));
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
    DATA_LOGGER->close();
    ERROR_HANDLER->close();
}
