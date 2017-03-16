/*
 * AIEngine.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "AIEngine.h"
#include "MotorConstants.h"
#include "utils/OperatorFunctions.h"
#include <cstdlib>

AIEngine::AIEngine()
{
    m_Motors.clear();
    m_Motors.push_back(Motor(MOTOR1DIR, MOTOR1EN));
    m_Motors.push_back(Motor(MOTOR2DIR, MOTOR2EN));
    //Motors.push_back(Motor(MOTOR3DIR, MOTOR3EN));

    m_memories.clear();

    m_imu.startThread();
}


AIEngine::~AIEngine()
{
}


void AIEngine::threadRoutine()
{
    learnConfiguration();
    followTargets();
}


void AIEngine::learnConfiguration()
{
    std::string logString = "";
    std::string newMemoryTitle = "new memory";

    // if(Confidence < CONFIDENCE_LEVEL)
    // {
        int motorUsedMask = 1;

        // Each motor individually
        for (vector<Motor>::iterator iter = m_Motors.begin(); iter != m_Motors.end(); iter++)
        {
            for (int motorOnTime_s = 2; motorOnTime_s < 8; motorOnTime_s += 2)
            {
                Memory newMem;
                newMem.m_initial = m_imu.getCurrentState();
                newMem.m_timeElapsed_s = motorOnTime_s;
                newMem.m_motorUsedMask = motorUsedMask;
                newMem.m_direction = motorUsedMask;
                executeMemory(newMem);
                newMem.m_final = m_imu.getCurrentState();
                newMem.m_confidence = 50;
                m_memories.push_back(newMem);

                logMemory(newMemoryTitle, newMem);

                usleep(2000000);

                newMem.m_initial = m_imu.getCurrentState();
                newMem.m_timeElapsed_s = motorOnTime_s;
                newMem.m_motorUsedMask = motorUsedMask;
                newMem.m_direction = 0;
                executeMemory(newMem);
                newMem.m_final = m_imu.getCurrentState();
                newMem.m_confidence = 50;
                m_memories.push_back(newMem);

                logMemory(newMemoryTitle, newMem);

                usleep(2000000);
            }

            motorUsedMask = motorUsedMask << 1;
        }

        usleep(2000000);

        // Both motors going the same direction
        for (int t = 2; t < 8; t += 2)
        {
            Memory newMem;
            newMem.m_initial = m_imu.getCurrentState();
            newMem.m_timeElapsed_s = t;
            newMem.m_motorUsedMask = 3;
            newMem.m_direction = 3;
            executeMemory(newMem);
            newMem.m_final = m_imu.getCurrentState();
            newMem.m_confidence = 50;
            m_memories.push_back(newMem);

            logMemory(newMemoryTitle, newMem);

            usleep(2000000);

            newMem.m_initial = m_imu.getCurrentState();
            newMem.m_timeElapsed_s = t;
            newMem.m_motorUsedMask = 3;
            newMem.m_direction = 0;
            executeMemory(newMem);
            newMem.m_final = m_imu.getCurrentState();
            newMem.m_confidence = 50;
            m_memories.push_back(newMem);

            logMemory(newMemoryTitle, newMem);

            usleep(2000000);
        }

        usleep(2000000);

        // Both motors going opposite
        for (int t = 2; t < 8; t += 2)
        {
            Memory newMem;
            newMem.m_initial = m_imu.getCurrentState();
            newMem.m_timeElapsed_s = t;
            newMem.m_motorUsedMask = 3;
            newMem.m_direction = 1;
            executeMemory(newMem);
            newMem.m_final = m_imu.getCurrentState();
            newMem.m_confidence = 50;
            m_memories.push_back(newMem);

            logMemory(newMemoryTitle, newMem);

            usleep(2000000);

            newMem.m_initial = m_imu.getCurrentState();
            newMem.m_timeElapsed_s = t;
            newMem.m_motorUsedMask = 3;
            newMem.m_direction = 2;
            executeMemory(newMem);
            newMem.m_final = m_imu.getCurrentState();
            newMem.m_confidence = 50;
            m_memories.push_back(newMem);

            logMemory(newMemoryTitle, newMem);

            usleep(2000000);
        }
    // }
}


void AIEngine::followTargets()
{
    string logstring = "";

    //driving phase
    while (1)
    {
        State initial = m_imu.getCurrentState();
        m_navigator.UpdateTarget(initial);
        State target = m_navigator.GetTarget();
        logState("target", target);

        target = initial - target;
        logState("diff", target);

        Memory* actionToTake = getBestMemory(target);
        logMemory("chosen memory", *actionToTake);

        State prediction = actionToTake->m_final - actionToTake->m_initial;
        logState("prediction", prediction);

        executeMemory(*actionToTake);

        State Final = m_imu.getCurrentState();
        State result = Final - initial;
        logState("result", result);

        float optimization = compareStates(result, prediction);
        float ideal = compareStates(prediction, prediction);

        logstring = "opt= ";
        logstring = logstring + optimization + " ideal= " + ideal;
        DATA_LOGGER->recordData(logstring);

        if (optimization <= ideal && optimization > (0.5 * ideal))
        {
            actionToTake->m_confidence += 10;
            if (actionToTake->m_confidence > 100)
                actionToTake->m_confidence = 100;

            DATA_LOGGER->recordData("memory correct");
        }
        else
        {
            Memory* Replacement = getBestMemory(result);
            float newopt = compareStates(result, Replacement->m_final - Replacement->m_initial);

            if (newopt > optimization)
            {
                Replacement->m_confidence += 10;
                if (Replacement->m_confidence > 100)
                    Replacement->m_confidence = 100;

                actionToTake->m_confidence -= 10;
                if (actionToTake->m_confidence < 0)
                    actionToTake->m_confidence = 0;

                DATA_LOGGER->recordData("found better memory, adjusting");
            }
            else if (newopt <= optimization)
            {
                actionToTake->m_initial = initial;
                actionToTake->m_final = Final;
                actionToTake->m_confidence -= 10;

                if (actionToTake->m_confidence < 0)
                    actionToTake->m_confidence = 0;

                DATA_LOGGER->recordData("Adjusting memory");
            }
        }

        usleep(1000000);
    }
}


Memory* AIEngine::getBestMemory(const State& Target)
{
    float maxOptimization = 0;
    int seed = rand() % 100 / m_memories.size();
    vector<Memory>::iterator ReturnedMemory = m_memories.begin();
    for (int i = 0; i < seed - 1; i++)
        ReturnedMemory++;

    for (vector<Memory>::iterator iter = m_memories.begin(); iter != m_memories.end(); iter++)
    {
        State diff = iter->m_final - iter->m_initial;
        float optimization = compareStates(diff, Target);

        if (optimization > maxOptimization && iter->m_confidence >= ReturnedMemory->m_confidence)
        {
            maxOptimization = optimization;
            ReturnedMemory = iter;
        }
    }

    return &(*ReturnedMemory);
}


float AIEngine::compareStates(const State& state1, const State& state2)
{
    float dotproduct = state1.m_displacement.x * state2.m_displacement.x + state1.m_displacement.y * state2.m_displacement.y
            + state1.m_displacement.z * state2.m_displacement.z + state1.m_angPosition.yaw * state2.m_angPosition.yaw
            + state1.m_angPosition.pitch * state2.m_angPosition.pitch + state1.m_angPosition.roll * state2.m_angPosition.roll;

    return dotproduct;
}


void AIEngine::executeMemory(const Memory& mem)
{
    int base = 1;
    for (vector<Motor>::iterator iter = m_Motors.begin(); iter != m_Motors.end(); iter++)
    {
        if (mem.m_motorUsedMask & base)
        {
            if (mem.m_direction & base)
                iter->forward();
            else
                iter->reverse();

            iter->on();
        }

        base = base << 1;
    }

    usleep(mem.m_timeElapsed_s * 1000000);

    for (vector<Motor>::iterator iter = m_Motors.begin(); iter != m_Motors.end(); iter++)
        iter->off();
}


void AIEngine::logMemory(const std::string& title, const Memory& mem)
{
    string str = title + " ";

    State diff = mem.m_final - mem.m_initial;

    str = str + mem.m_motorUsedMask + " " + mem.m_direction + " " + mem.m_timeElapsed_s + " " + mem.m_confidence + " "
            + diff.m_displacement.x + " " + diff.m_displacement.y + " " + diff.m_displacement.z + " " + diff.m_angPosition.roll + " "
            + diff.m_angPosition.pitch + " " + diff.m_angPosition.yaw;

    DATA_LOGGER->recordData(str);
}


void AIEngine::logState(const std::string& title, const State& state)
{
    std::string logstring = title + " ";

    logstring = logstring + state.m_displacement.x + " " + state.m_displacement.y + " " + state.m_displacement.z + " "
            + state.m_angPosition.roll + " " + state.m_angPosition.pitch + " " + state.m_angPosition.yaw;

    DATA_LOGGER->recordData(logstring);
}
