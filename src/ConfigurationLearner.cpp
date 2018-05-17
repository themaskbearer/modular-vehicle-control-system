/*
 * ConfigurationLearner.cpp
 *
 *  Created on: May 17, 2018
 *      Author: jpollard
 */

#include "ConfigurationLearner.h"
#include "utils/DataLogger.h"
#include <cmath>

ConfigurationLearner::ConfigurationLearner(unsigned int numOfMotors, MemoryStorage* memories) :
    MovementController(memories),
    m_numOfMotors(numOfMotors)
{
    int numberOfCombinations =std::pow(2, m_numOfMotors) - 1;
    for(int motorsUsedMask = 1; motorsUsedMask <= numberOfCombinations; ++motorsUsedMask)
    {
        addMotorDirectionCombinations(motorsUsedMask);
    }
}


void ConfigurationLearner::addMotorDirectionCombinations(unsigned int motorsUsedMask)
{
    for(unsigned int motorDirectionMask = 0; motorDirectionMask <= motorsUsedMask; ++motorDirectionMask)
    {
        // If any bits in the motor direction mask matches any of the bits in the motor used mask
        if( ((motorsUsedMask & motorDirectionMask) == motorDirectionMask) || motorDirectionMask == 0)
        {
            addDurationVariations(motorsUsedMask, motorDirectionMask);
        }
    }
}


void ConfigurationLearner::addDurationVariations(unsigned int motorsUsedMask, unsigned int motorDirectionMask)
{
    static std::vector<int> secondsToRun = {2, 4, 6};

    for(int timeToRun : secondsToRun)
    {
        m_motorsUsed.push_back(motorsUsedMask);
        m_motorDirections.push_back(motorDirectionMask);
        m_times_s.push_back(timeToRun);
    }
}


ConfigurationLearner::~ConfigurationLearner()
{

}


VehicleCommand ConfigurationLearner::getCommandToExecute(const State& currentTarget, const State& currentState)
{
    VehicleCommand command;

    if(!isLearningComplete())
    {
        currentMemory = Memory();

        command.m_motorUsedMask = m_motorsUsed[m_learningIndex];
        command.m_directionMask = m_motorDirections[m_learningIndex];
        command.m_timeElapsed_s = m_times_s[m_learningIndex];

        currentMemory.m_command = command;
        currentMemory.m_initial = currentState;
    }

    return command;
}


void ConfigurationLearner::processCommandResults(const State& finalState)
{
    if(!isLearningComplete())
    {
        currentMemory.m_final = finalState;
        currentMemory.m_confidence = INITIAL_CONFIDENCE;
        m_memories->push_back(currentMemory);

        DATA_LOGGER->recordData("New Memory:\n" + currentMemory.to_str());

        ++m_learningIndex;
    }
}
