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
    Motors.clear();
    Motors.push_back(Motor(MOTOR1DIR, MOTOR1EN));
    Motors.push_back(Motor(MOTOR2DIR, MOTOR2EN));
    //Motors.push_back(Motor(MOTOR3DIR, MOTOR3EN));

    Memories.clear();

    Confidence = 0;

    IMU.StartThread();
}


AIEngine::~AIEngine()
{
}


void AIEngine::ThreadRoutine()
{
    string logstring = "";

    // if(Confidence < CONFIDENCE_LEVEL)
    // {
        int MotorNumber = 1;
        for (vector<Motor>::iterator iter = Motors.begin(); iter != Motors.end(); iter++)
        {
            for (int t = 2; t < 8; t += 2)
            {
                Memory NewMem;
                NewMem.Initial = IMU.getCurrentState();
                NewMem.deltaT = t;
                NewMem.MotorUsed = MotorNumber;
                NewMem.direction = MotorNumber;
                ExecuteMemory(NewMem);
                NewMem.Final = IMU.getCurrentState();
                NewMem.confidence = 50;
                Memories.push_back(NewMem);

                logstring = "new memory ";
                logstring += LogMemory(NewMem);
                DataLogger::recorddata(logstring);

                usleep(2000000);

                NewMem.Initial = IMU.getCurrentState();
                NewMem.deltaT = t;
                NewMem.MotorUsed = MotorNumber;
                NewMem.direction = 0;
                ExecuteMemory(NewMem);
                NewMem.Final = IMU.getCurrentState();
                NewMem.confidence = 50;
                Memories.push_back(NewMem);

                logstring = "new memory ";
                logstring += LogMemory(NewMem);
                DataLogger::recorddata(logstring);

                usleep(2000000);
            }

            MotorNumber = MotorNumber << 1;
        }

        usleep(2000000);

        for (int t = 2; t < 8; t += 2)
        {
            Memory NewMem;
            NewMem.Initial = IMU.getCurrentState();
            NewMem.deltaT = t;
            NewMem.MotorUsed = 3;
            NewMem.direction = 3;
            ExecuteMemory(NewMem);
            NewMem.Final = IMU.getCurrentState();
            NewMem.confidence = 50;
            Memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += LogMemory(NewMem);
            DataLogger::recorddata(logstring);

            usleep(2000000);

            NewMem.Initial = IMU.getCurrentState();
            NewMem.deltaT = t;
            NewMem.MotorUsed = 3;
            NewMem.direction = 0;
            ExecuteMemory(NewMem);
            NewMem.Final = IMU.getCurrentState();
            NewMem.confidence = 50;
            Memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += LogMemory(NewMem);
            DataLogger::recorddata(logstring);

            usleep(2000000);
        }

        usleep(2000000);

        for (int t = 2; t < 8; t += 2)
        {
            Memory NewMem;
            NewMem.Initial = IMU.getCurrentState();
            NewMem.deltaT = t;
            NewMem.MotorUsed = 3;
            NewMem.direction = 1;
            ExecuteMemory(NewMem);
            NewMem.Final = IMU.getCurrentState();
            NewMem.confidence = 50;
            Memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += LogMemory(NewMem);
            DataLogger::recorddata(logstring);

            usleep(2000000);

            NewMem.Initial = IMU.getCurrentState();
            NewMem.deltaT = t;
            NewMem.MotorUsed = 3;
            NewMem.direction = 2;
            ExecuteMemory(NewMem);
            NewMem.Final = IMU.getCurrentState();
            NewMem.confidence = 50;
            Memories.push_back(NewMem);

            logstring = "new memory ";
            logstring += LogMemory(NewMem);
            DataLogger::recorddata(logstring);

            usleep(2000000);
        }
    // }

    //driving phase
    while (1)
    {
        State Initial = IMU.getCurrentState();
        Navigator.UpdateTarget(Initial);
        State Target = Navigator.GetTarget();

        logstring = "target ";
        logstring = logstring + Target.Displacement.x + " " + Target.Displacement.y + " " + Target.Displacement.z;
        DataLogger::recorddata(logstring);

        Target = Initial - Target;

        logstring = "diff ";
        logstring = logstring + Target.Displacement.x + " " + Target.Displacement.y + " " + Target.Displacement.z + " "
                + Target.RPY.roll + " " + Target.RPY.pitch + " " + Target.RPY.yaw;
        DataLogger::recorddata(logstring);

        Memory* ActiontoTake = getBestMemory(Target);

        logstring = "chosen memory ";
        logstring += LogMemory(*ActiontoTake);
        DataLogger::recorddata(logstring);

        State prediction = ActiontoTake->Final - ActiontoTake->Initial;

        logstring = "prediction ";
        logstring = logstring + prediction.Displacement.x + " " + prediction.Displacement.y + " "
                + prediction.Displacement.z + " " + prediction.RPY.roll + " " + prediction.RPY.pitch + " "
                + prediction.RPY.yaw;
        DataLogger::recorddata(logstring);

        ExecuteMemory(*ActiontoTake);

        State Final = IMU.getCurrentState();
        State diff = Final - Initial;

        logstring = "result ";
        logstring = logstring + diff.Displacement.x + " " + diff.Displacement.y + " " + diff.Displacement.z + " "
                + diff.RPY.roll + " " + diff.RPY.pitch + " " + diff.RPY.yaw;
        DataLogger::recorddata(logstring);

        float opt = CompareStates(diff, prediction);
        float ideal = CompareStates(prediction, prediction);

        logstring = "opt= ";
        logstring = logstring + opt + " ideal= " + ideal;
        DataLogger::recorddata(logstring);

        if (opt <= ideal && opt > (0.5 * ideal))
        {
            ActiontoTake->confidence += 10;
            if (ActiontoTake->confidence > 100)
                ActiontoTake->confidence = 100;

            logstring = "memory correct";
            DataLogger::recorddata(logstring);
        }
        else
        {
            Memory* Replacement = getBestMemory(diff);
            float newopt = CompareStates(diff, Replacement->Final - Replacement->Initial);

            if (newopt > opt)
            {
                Replacement->confidence += 10;
                if (Replacement->confidence > 100)
                    Replacement->confidence = 100;

                ActiontoTake->confidence -= 10;
                if (ActiontoTake->confidence < 0)
                    ActiontoTake->confidence = 0;

                logstring = "found better memory, adjusting";
                DataLogger::recorddata(logstring);
            }
            else if (newopt <= opt)
            {
                ActiontoTake->Initial = Initial;
                ActiontoTake->Final = Final;
                ActiontoTake->confidence -= 10;

                if (ActiontoTake->confidence < 0)
                    ActiontoTake->confidence = 0;

                logstring = "Adjusting memory";
                DataLogger::recorddata(logstring);
            }
        }

        usleep(1000000);
    }
}


Memory* AIEngine::getBestMemory(State Target)
{
    float maxoptimization = 0;
    int seed = rand() % 100 / Memories.size();
    vector<Memory>::iterator ReturnedMemory = Memories.begin();
    for (int i = 0; i < seed - 1; i++)
        ReturnedMemory++;

    for (vector<Memory>::iterator iter = Memories.begin(); iter != Memories.end(); iter++)
    {
        State diff = iter->Final - iter->Initial;
        float opt = CompareStates(diff, Target);

        if (opt > maxoptimization && iter->confidence >= ReturnedMemory->confidence)
        {
            maxoptimization = opt;
            ReturnedMemory = iter;
        }
    }

    return &(*ReturnedMemory);
}


float AIEngine::CompareStates(State state1, State state2)
{
    float dotproduct = state1.Displacement.x * state2.Displacement.x + state1.Displacement.y * state2.Displacement.y
            + state1.Displacement.z * state2.Displacement.z + state1.RPY.yaw * state2.RPY.yaw
            + state1.RPY.pitch * state2.RPY.pitch + state1.RPY.roll * state2.RPY.roll;

    return dotproduct;
}


void AIEngine::ExecuteMemory(Memory mem)
{
    int base = 1;
    for (vector<Motor>::iterator iter = Motors.begin(); iter != Motors.end(); iter++)
    {
        if (mem.MotorUsed & base)
        {
            if (mem.direction & base)
                iter->Forward();
            else
                iter->Reverse();

            iter->On();
        }

        base = base << 1;
    }

    usleep(mem.deltaT * 1000000);

    for (vector<Motor>::iterator iter = Motors.begin(); iter != Motors.end(); iter++)
        iter->Off();
}


string AIEngine::LogMemory(Memory mem)
{
    string str = "";

    State diff = mem.Final - mem.Initial;

    str = str + mem.MotorUsed + " " + mem.direction + " " + mem.deltaT + " " + mem.confidence + " "
            + diff.Displacement.x + " " + diff.Displacement.y + " " + diff.Displacement.z + " " + diff.RPY.roll + " "
            + diff.RPY.pitch + " " + diff.RPY.yaw;

    return str;
}

