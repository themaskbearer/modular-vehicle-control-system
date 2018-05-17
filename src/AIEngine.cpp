/*
 * AIEngine.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "AIEngine.h"
#include "utils/DataLogger.h"
#include "utils/OperatorFunctions.h"
#include <cstdlib>

AIEngine::AIEngine(MemoryStorage* memories) :
    MovementController(memories)
{

}


AIEngine::~AIEngine()
{
}


VehicleCommand AIEngine::getCommandToExecute(const State& currentTarget, const State& currentState)
{
    logState("target", currentTarget);

    m_currentMoveInitialState = currentState;
    State poseDifference = currentState - currentTarget;
    logState("diff", poseDifference);

    m_currentActingMemory = getBestMemory(poseDifference);
    DATA_LOGGER->recordData("chosen memory" + m_currentActingMemory->to_str());

    m_currentMovePrediction = m_currentActingMemory->m_final - m_currentActingMemory->m_initial;
    logState("prediction", m_currentMovePrediction);

    return m_currentActingMemory->m_command;
}


void AIEngine::processCommandResults(const State& finalState)
{
    State result = finalState - m_currentMoveInitialState;
    logState("result", result);

    float optimization = compareStates(result, m_currentMovePrediction);
    float ideal = compareStates(m_currentMovePrediction, m_currentMovePrediction);

    std::string logstring = "opt= ";
    logstring = logstring + optimization + " ideal= " + ideal;
    DATA_LOGGER->recordData(logstring);

    if (optimization <= ideal && optimization > (0.5 * ideal))
    {
        m_currentActingMemory->m_confidence += 10;
        if (m_currentActingMemory->m_confidence > 100)
            m_currentActingMemory->m_confidence = 100;

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

            m_currentActingMemory->m_confidence -= 10;
            if (m_currentActingMemory->m_confidence < 0)
                m_currentActingMemory->m_confidence = 0;

            DATA_LOGGER->recordData("found better memory, adjusting");
        }
        else if (newopt <= optimization)
        {
            m_currentActingMemory->m_initial = m_currentMoveInitialState;
            m_currentActingMemory->m_final = finalState;
            m_currentActingMemory->m_confidence -= 10;

            if (m_currentActingMemory->m_confidence < 0)
                m_currentActingMemory->m_confidence = 0;

            DATA_LOGGER->recordData("Adjusting memory");
        }
    }
}


Memory* AIEngine::getBestMemory(const State& Target)
{
    float maxOptimization = 0;
    int seed = rand() % 100 / m_memories.size();
    std::vector<Memory>::iterator ReturnedMemory = m_memories.begin();
    for (int i = 0; i < seed - 1; i++)
        ReturnedMemory++;

    for (std::vector<Memory>::iterator iter = m_memories.begin(); iter != m_memories.end(); iter++)
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


void AIEngine::logState(const std::string& title, const State& state)
{
    std::string logstring = title + " ";

    logstring = logstring + state.m_displacement.x + " " + state.m_displacement.y + " " + state.m_displacement.z + " "
            + state.m_angPosition.roll + " " + state.m_angPosition.pitch + " " + state.m_angPosition.yaw;

    DATA_LOGGER->recordData(logstring);
}
