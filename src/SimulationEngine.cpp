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

State SimulationEngine::makeMovement(Memory memToMove)
{
        switch(memToMove.m_motorUsed)
        {
                case 1:
                        if(memToMove.m_direction & 1)
                                CurrentState.m_angPosition.yaw += memToMove.m_timeElapsed_s*M_PI/8;
                        else
                                CurrentState.m_angPosition.yaw -= memToMove.m_timeElapsed_s*M_PI/8;
                        break;
                case 2:
                        if(memToMove.m_direction & 2)
                                CurrentState.m_angPosition.yaw -= memToMove.m_timeElapsed_s*M_PI/8;
                        else
                                CurrentState.m_angPosition.yaw += memToMove.m_timeElapsed_s*M_PI/8;
                        break;
                case 3:
                        if(memToMove.m_direction == 3)
                        {
                                CurrentState.m_displacement.x +=
                                        memToMove.m_timeElapsed_s*0.5*cos(CurrentState.m_angPosition.yaw);
                                CurrentState.m_displacement.y +=
                                        memToMove.m_timeElapsed_s*0.5*sin(CurrentState.m_angPosition.yaw);
                        }
                        else if(memToMove.m_direction == 0)
                        {
                                CurrentState.m_displacement.x -=
                                        memToMove.m_timeElapsed_s*0.5*cos(CurrentState.m_angPosition.yaw);
                                CurrentState.m_displacement.y -=
                                        memToMove.m_timeElapsed_s*0.5*sin(CurrentState.m_angPosition.yaw);
                        }
                        else if(memToMove.m_direction == 1)
                                CurrentState.m_angPosition.yaw += memToMove.m_timeElapsed_s*M_PI/4;
                        else
                                CurrentState.m_angPosition.yaw -= memToMove.m_timeElapsed_s*M_PI/4;
                        break;
        }
        return CurrentState;
}

State SimulationEngine::getInitialState()
{
        return CurrentState;
}



