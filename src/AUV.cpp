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

}


AUV::~AUV()
{

}


void AUV::initialize()
{
    m_vehicle.reset(new SimulatedVehicle());
    m_supervisor.reset(new ControlSystem(m_vehicle));
}


void AUV::run()
{

}


void AUV::shutdown()
{

}
