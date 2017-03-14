/*
 * AIEngine.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "AIEngine.h"
#include "MotorConstants.h"
#include "OperatorFunctions.h"
#include <cstdlib>

AIEngine::AIEngine()
{
    m_Motors.clear();
    m_Motors.push_back(Motor(MOTOR1DIR, MOTOR1EN));
    m_Motors.push_back(Motor(MOTOR2DIR, MOTOR2EN));
    //Motors.push_back(Motor(MOTOR3DIR, MOTOR3EN));

    m_memories.clear();

    m_confidence = 0;

    m_imu.startThread();
}


AIEngine::~AIEngine()
{
}


void AIEngine::threadRoutine()
{
    string logstring = "";

    // if(Confidence < CONFIDENCE_LEVEL)
    // {
        int MotorNumber = 1;
        for (vector<Motor>::iterator iter = m_Motors.begin(); iter != m_Motors.end(); iter++)
        {
            for (int t = 2; t < 8; t += 2)
            {
                Memory NewMem;
                NewMem.m_initial = m_imu.getCurrentState();
                NewMem.m_timeElapsed_s = t;
                NewMem.m_motorUsed = MotorNumber;
                NewMem.m_direction = MotorNumber;
                executeMemory(NewMem);
                NewMem.m_final = m_imu.getCurrentState();
                NewMem.m_confidence = 50;
                m_memories.push_back(NewMem);

                logstring = "new memory ";
                logstring += logMemory(NewMem);
                DATA_LOGGER->recordData(logstring);

                usleep(2000000);

                NewMem.m_initial = m_imu.getCurrentState();
                NewMem.m_timeElapsed_s = t;
                NewMem.m_motorUsed = MotorNumber;
                NewMem.m_direction = 0;
                executeMemory(NewMem);
                NewMem.m_final = m_imu.getCurrentState();
                NewMem.m_confidence = 50;
                m_memories.push_back(NewMem);

                logstring = "new memory ";
                logstring += logMemory(NewMem);
                DATA_LOGGER->recordData(logstring);

                usleep(2000000);
            }

            MotorNumber = MotorNumber << 1;
        }

        usleep(2000000);

        for (int t = 2; t < 8; t += 2)
        {
            Memory NewMem;
            NewMem.m_initial = m_imu.getCurrentState();
            NewMem.m_timeElapsed_s = t;
            NewMem.m_motorUsed = 3;
            NewMem.m_direction = 3;
            executeMemory(NewMem);
            NewMem.m_final = m_imu.getCurrentState();
            NewMem.m_confidence = 50;
            m_memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += logMemory(NewMem);
            DATA_LOGGER->recordData(logstring);

            usleep(2000000);

            NewMem.m_initial = m_imu.getCurrentState();
            NewMem.m_timeElapsed_s = t;
            NewMem.m_motorUsed = 3;
            NewMem.m_direction = 0;
            executeMemory(NewMem);
            NewMem.m_final = m_imu.getCurrentState();
            NewMem.m_confidence = 50;
            m_memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += logMemory(NewMem);
            DATA_LOGGER->recordData(logstring);

            usleep(2000000);
        }

        usleep(2000000);

        for (int t = 2; t < 8; t += 2)
        {
            Memory NewMem;
            NewMem.m_initial = m_imu.getCurrentState();
            NewMem.m_timeElapsed_s = t;
            NewMem.m_motorUsed = 3;
            NewMem.m_direction = 1;
            executeMemory(NewMem);
            NewMem.m_final = m_imu.getCurrentState();
            NewMem.m_confidence = 50;
            m_memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += logMemory(NewMem);
            DATA_LOGGER->recordData(logstring);

            usleep(2000000);

            NewMem.m_initial = m_imu.getCurrentState();
            NewMem.m_timeElapsed_s = t;
            NewMem.m_motorUsed = 3;
            NewMem.m_direction = 2;
            executeMemory(NewMem);
            NewMem.m_final = m_imu.getCurrentState();
            NewMem.m_confidence = 50;
            m_memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += logMemory(NewMem);
            DATA_LOGGER->recordData(logstring);

            usleep(2000000);
        }
    // }

    //driving phase
    while (1)
    {
        State Initial = m_imu.getCurrentState();
        m_navigator.UpdateTarget(Initial);
        State Target = m_navigator.GetTarget();

        logstring = "target ";
        logstring = logstring + Target.m_displacement.x + " " + Target.m_displacement.y + " " + Target.m_displacement.z;
        DATA_LOGGER->recordData(logstring);

        Target = Initial - Target;

        logstring = "diff ";
        logstring = logstring + Target.m_displacement.x + " " + Target.m_displacement.y + " " + Target.m_displacement.z + " "
                + Target.m_angPosition.roll + " " + Target.m_angPosition.pitch + " " + Target.m_angPosition.yaw;
        DATA_LOGGER->recordData(logstring);

        Memory* ActiontoTake = getBestMemory(Target);

        logstring = "chosen memory ";
        logstring += logMemory(*ActiontoTake);
        DATA_LOGGER->recordData(logstring);

        State prediction = ActiontoTake->m_final - ActiontoTake->m_initial;

        logstring = "prediction ";
        logstring = logstring + prediction.m_displacement.x + " " + prediction.m_displacement.y + " "
                + prediction.m_displacement.z + " " + prediction.m_angPosition.roll + " " + prediction.m_angPosition.pitch + " "
                + prediction.m_angPosition.yaw;
        DATA_LOGGER->recordData(logstring);

        executeMemory(*ActiontoTake);

        State Final = m_imu.getCurrentState();
        State diff = Final - Initial;

        logstring = "result ";
        logstring = logstring + diff.m_displacement.x + " " + diff.m_displacement.y + " " + diff.m_displacement.z + " "
                + diff.m_angPosition.roll + " " + diff.m_angPosition.pitch + " " + diff.m_angPosition.yaw;
        DATA_LOGGER->recordData(logstring);

        float opt = compareStates(diff, prediction);
        float ideal = compareStates(prediction, prediction);

        logstring = "opt= ";
        logstring = logstring + opt + " ideal= " + ideal;
        DATA_LOGGER->recordData(logstring);

        if (opt <= ideal && opt > (0.5 * ideal))
        {
            ActiontoTake->m_confidence += 10;
            if (ActiontoTake->m_confidence > 100)
                ActiontoTake->m_confidence = 100;

            logstring = "memory correct";
            DATA_LOGGER->recordData(logstring);
        }
        else
        {
            Memory* Replacement = getBestMemory(diff);
            float newopt = compareStates(diff, Replacement->m_final - Replacement->m_initial);

            if (newopt > opt)
            {
                Replacement->m_confidence += 10;
                if (Replacement->m_confidence > 100)
                    Replacement->m_confidence = 100;

                ActiontoTake->m_confidence -= 10;
                if (ActiontoTake->m_confidence < 0)
                    ActiontoTake->m_confidence = 0;

                logstring = "found better memory, adjusting";
                DATA_LOGGER->recordData(logstring);
            }
            else if (newopt <= opt)
            {
                ActiontoTake->m_initial = Initial;
                ActiontoTake->m_final = Final;
                ActiontoTake->m_confidence -= 10;

                if (ActiontoTake->m_confidence < 0)
                    ActiontoTake->m_confidence = 0;

                logstring = "Adjusting memory";
                DATA_LOGGER->recordData(logstring);
            }
        }

        usleep(1000000);
    }
}


Memory* AIEngine::getBestMemory(State Target)
{
    float maxoptimization = 0;
    int seed = rand() % 100 / m_memories.size();
    vector<Memory>::iterator ReturnedMemory = m_memories.begin();
    for (int i = 0; i < seed - 1; i++)
        ReturnedMemory++;

    for (vector<Memory>::iterator iter = m_memories.begin(); iter != m_memories.end(); iter++)
    {
        State diff = iter->m_final - iter->m_initial;
        float opt = compareStates(diff, Target);

        if (opt > maxoptimization && iter->m_confidence >= ReturnedMemory->m_confidence)
        {
            maxoptimization = opt;
            ReturnedMemory = iter;
        }
    }

    return &(*ReturnedMemory);
}


float AIEngine::compareStates(State state1, State state2)
{
    float dotproduct = state1.m_displacement.x * state2.m_displacement.x + state1.m_displacement.y * state2.m_displacement.y
            + state1.m_displacement.z * state2.m_displacement.z + state1.m_angPosition.yaw * state2.m_angPosition.yaw
            + state1.m_angPosition.pitch * state2.m_angPosition.pitch + state1.m_angPosition.roll * state2.m_angPosition.roll;

    return dotproduct;
}


void AIEngine::executeMemory(Memory mem)
{
    int base = 1;
    for (vector<Motor>::iterator iter = m_Motors.begin(); iter != m_Motors.end(); iter++)
    {
        if (mem.m_motorUsed & base)
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


string AIEngine::logMemory(Memory mem)
{
    string str = "";

    State diff = mem.m_final - mem.m_initial;

    str = str + mem.m_motorUsed + " " + mem.m_direction + " " + mem.m_timeElapsed_s + " " + mem.m_confidence + " "
            + diff.m_displacement.x + " " + diff.m_displacement.y + " " + diff.m_displacement.z + " " + diff.m_angPosition.roll + " "
            + diff.m_angPosition.pitch + " " + diff.m_angPosition.yaw;

    return str;
}

