/*
 * AUV.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: jpollard
 */

#include "AUV.h"
#include "utils/Configuration.h"
#include "SimulatedVehicle.h"
#include "TestPlatform.h"
#include "ControlSystem.h"



AUV::AUV()
{
    std::string vehicleType = CONFIG.getValue(VEHICLE_TYPE);
    if(vehicleType == "test_platform")
        _vehicle = std::make_shared<TestPlatform>();
    else
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
    _supervisor->stop();
    _vehicle->stop();
}
