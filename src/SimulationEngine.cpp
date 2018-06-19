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
        switch(command._motorUsedMask)
        {
                case 1:
                        if(command._directionMask & 1)
                                CurrentState._angPosition.yaw += command._timeElapsed_s*M_PI/8;
                        else
                                CurrentState._angPosition.yaw -= command._timeElapsed_s*M_PI/8;
                        break;
                case 2:
                        if(command._directionMask & 2)
                                CurrentState._angPosition.yaw -= command._timeElapsed_s*M_PI/8;
                        else
                                CurrentState._angPosition.yaw += command._timeElapsed_s*M_PI/8;
                        break;
                case 3:
                        if(command._directionMask == 3)
                        {
                                CurrentState._displacement.x +=
                                        command._timeElapsed_s*0.5*cos(CurrentState._angPosition.yaw);
                                CurrentState._displacement.y +=
                                        command._timeElapsed_s*0.5*sin(CurrentState._angPosition.yaw);
                        }
                        else if(command._directionMask == 0)
                        {
                                CurrentState._displacement.x -=
                                        command._timeElapsed_s*0.5*cos(CurrentState._angPosition.yaw);
                                CurrentState._displacement.y -=
                                        command._timeElapsed_s*0.5*sin(CurrentState._angPosition.yaw);
                        }
                        else if(command._directionMask == 1)
                                CurrentState._angPosition.yaw += command._timeElapsed_s*M_PI/4;
                        else
                                CurrentState._angPosition.yaw -= command._timeElapsed_s*M_PI/4;
                        break;
        }
}

State SimulationEngine::getState()
{
        return CurrentState;
}



