/*
 * SimulationEngine.cpp
 *
 * * Created on: Nov 22, 2012
 * * Author: jpollard
 * */

#include "SimulationEngine.h"
#define _USE_MATH_DEFINES
#include <cmath>
using std::exp;
using std::log;
using std::cos;
using std::sin;
using std::abs;

SimulationEngine::SimulationEngine()
{
}

SimulationEngine::~SimulationEngine()
{
}

void SimulationEngine::makeMovement(const VehicleCommand& command)
{
        switch(command.m_motorUsedMask)
        {
                case 1:
                        if(command.m_directionMask & 1)
                                CurrentState.m_angPosition.yaw += command.m_timeElapsed_s*M_PI/8;
                        else
                                CurrentState.m_angPosition.yaw -= command.m_timeElapsed_s*M_PI/8;
                        break;
                case 2:
                        if(command.m_directionMask & 2)
                                CurrentState.m_angPosition.yaw -= command.m_timeElapsed_s*M_PI/8;
                        else
                                CurrentState.m_angPosition.yaw += command.m_timeElapsed_s*M_PI/8;
                        break;
                case 3:
                        if(command.m_directionMask == 3)
                        {
                                CurrentState.m_displacement.x +=
                                        command.m_timeElapsed_s*0.5*cos(CurrentState.m_angPosition.yaw);
                                CurrentState.m_displacement.y +=
                                        command.m_timeElapsed_s*0.5*sin(CurrentState.m_angPosition.yaw);
                        }
                        else if(command.m_directionMask == 0)
                        {
                                CurrentState.m_displacement.x -=
                                        command.m_timeElapsed_s*0.5*cos(CurrentState.m_angPosition.yaw);
                                CurrentState.m_displacement.y -=
                                        command.m_timeElapsed_s*0.5*sin(CurrentState.m_angPosition.yaw);
                        }
                        else if(command.m_directionMask == 1)
                                CurrentState.m_angPosition.yaw += command.m_timeElapsed_s*M_PI/4;
                        else
                                CurrentState.m_angPosition.yaw -= command.m_timeElapsed_s*M_PI/4;
                        break;
        }
}

State SimulationEngine::getState()
{
        return CurrentState;
}



