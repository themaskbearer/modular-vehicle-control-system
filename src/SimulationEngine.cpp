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
        CurrentState = getEmptyState();
}

SimulationEngine::~SimulationEngine()
{
}

State SimulationEngine::MakeMovement(Memory MemToMove)
{
        switch(MemToMove.MotorUsed)
        {
                case 1:
                        if(MemToMove.direction & 1)
                                CurrentState.RPY.yaw += MemToMove.deltaT*M_PI/8;
                        else
                                CurrentState.RPY.yaw -= MemToMove.deltaT*M_PI/8;
                        break;
                case 2:
                        if(MemToMove.direction & 2)
                                CurrentState.RPY.yaw -= MemToMove.deltaT*M_PI/8;
                        else
                                CurrentState.RPY.yaw += MemToMove.deltaT*M_PI/8;
                        break;
                case 3:
                        if(MemToMove.direction == 3)
                        {
                                CurrentState.Displacement.x +=
                                        MemToMove.deltaT*0.5*cos(CurrentState.RPY.yaw);
                                CurrentState.Displacement.y +=
                                        MemToMove.deltaT*0.5*sin(CurrentState.RPY.yaw);
                        }
                        else if(MemToMove.direction == 0)
                        {
                                CurrentState.Displacement.x -=
                                        MemToMove.deltaT*0.5*cos(CurrentState.RPY.yaw);
                                CurrentState.Displacement.y -=
                                        MemToMove.deltaT*0.5*sin(CurrentState.RPY.yaw);
                        }
                        else if(MemToMove.direction == 1)
                                CurrentState.RPY.yaw += MemToMove.deltaT*M_PI/4;
                        else
                                CurrentState.RPY.yaw -= MemToMove.deltaT*M_PI/4;
                        break;
        }
        return CurrentState;
}

State SimulationEngine::GetInitialState()
{
        return CurrentState;
}



