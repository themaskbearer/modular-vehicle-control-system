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
#include <cmath>

AIEngine::AIEngine(MemoryStorage* memories) :
    MovementController(memories)
{

}


AIEngine::~AIEngine()
{
}


VehicleCommand AIEngine::getCommandToExecute(const State& currentTarget, const State& currentState)
{
    DATA_LOGGER->recordData("\n-----------New iteration---------------");

    m_currentMoveInitialState = currentState;
    State poseDifference = currentTarget - currentState;
    logState("current pose: ", currentState);
    logState("target: ", currentTarget);
    logState("diff: ", poseDifference);

    m_currentActingMemory = getBestMemory(poseDifference);
    DATA_LOGGER->recordData("chosen memory: " + m_currentActingMemory->to_str());

    m_currentMovePrediction = m_currentActingMemory->m_final - m_currentActingMemory->m_initial;
    logState("prediction: ", m_currentMovePrediction);

    return m_currentActingMemory->m_command;
}


void AIEngine::processCommandResults(const State& finalState)
{
    State result = finalState - m_currentMoveInitialState;
    logState("result", result);

    float movementError = compareStates(result, m_currentMovePrediction);

    std::string logstring = "error= ";
    logstring = logstring + movementError;
    DATA_LOGGER->recordData(logstring);

//    if (movementError <= ideal && movementError > (0.5 * ideal))
//    {
//        m_currentActingMemory->m_confidence += 10;
//        if (m_currentActingMemory->m_confidence > 100)
//            m_currentActingMemory->m_confidence = 100;
//
//        DATA_LOGGER->recordData("memory correct");
//    }
//    else
//    {
//        Memory* Replacement = getBestMemory(result);
//        float newopt = compareStates(result, Replacement->m_final - Replacement->m_initial);
//
//        if (newopt > movementError)
//        {
//            Replacement->m_confidence += 10;
//            if (Replacement->m_confidence > 100)
//                Replacement->m_confidence = 100;
//
//            m_currentActingMemory->m_confidence -= 10;
//            if (m_currentActingMemory->m_confidence < 0)
//                m_currentActingMemory->m_confidence = 0;
//
//            DATA_LOGGER->recordData("found better memory, adjusting");
//        }
//        else if (newopt <= movementError)
//        {
//            m_currentActingMemory->m_initial = m_currentMoveInitialState;
//            m_currentActingMemory->m_final = finalState;
//            m_currentActingMemory->m_confidence -= 10;
//
//            if (m_currentActingMemory->m_confidence < 0)
//                m_currentActingMemory->m_confidence = 0;
//
//            DATA_LOGGER->recordData("Adjusting memory");
//        }
//    }
}


Memory* AIEngine::getBestMemory(const State& Target)
{
    int seed = rand() % 100 / m_memories->size();
    auto ReturnedMemory = m_memories->begin();
    // TODO: Fix this ridiculousness
    for(int i = 0; i < seed - 1; i++)
        ReturnedMemory++;

    // Set initial pose error and memory
    State diff = ReturnedMemory->m_final - ReturnedMemory->m_initial;
    float maxPoseError = compareStates(diff, Target);

    // TODO: Fix this too
    for(auto iter = m_memories->begin(); iter != m_memories->end(); ++iter)
    {
        diff = iter->m_final - iter->m_initial;
        float poseError = compareStates(diff, Target);

        if(poseError < maxPoseError && iter->m_confidence >= ReturnedMemory->m_confidence)
        {
            maxPoseError = poseError;
            ReturnedMemory = iter;
        }
    }

    return &(*ReturnedMemory);
}


float AIEngine::compareStates(const State& state1, const State& state2)
{
    float error = std::sqrt(std::pow(state1.m_displacement.x - state2.m_displacement.x, 2) +
                            std::pow(state1.m_displacement.y - state2.m_displacement.y, 2) +
                            std::pow(state1.m_displacement.z - state2.m_displacement.z, 2) +
                            std::pow(state1.m_angPosition.yaw - state2.m_angPosition.yaw, 2) +
                            std::pow(state1.m_angPosition.pitch - state2.m_angPosition.pitch, 2) +
                            std::pow(state1.m_angPosition.roll - state2.m_angPosition.roll, 2) );

    return error;
}


void AIEngine::logState(const std::string& title, const State& state)
{
    std::string logstring = title + " ";

    logstring = logstring + state.m_displacement.x + " " + state.m_displacement.y + " " + state.m_displacement.z + " "
            + state.m_angPosition.roll + " " + state.m_angPosition.pitch + " " + state.m_angPosition.yaw;

    DATA_LOGGER->recordData(logstring);
}
