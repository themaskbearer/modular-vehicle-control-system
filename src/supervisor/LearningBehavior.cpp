/*
 * ConfigurationLearner.cpp
 *
 *  Created on: May 17, 2018
 *      Author: jpollard
 */

#include "LearningBehavior.h"
#include "utils/DataLogger.h"
#include <cmath>

LearningBehavior::LearningBehavior(unsigned int numOfMotors, MemoryStorage* memories) :
    _numOfMotors(numOfMotors),
    _memories(memories)
{
    int numberOfCombinations =std::pow(2, _numOfMotors) - 1;
    for(int motorsUsedMask = 1; motorsUsedMask <= numberOfCombinations; ++motorsUsedMask)
    {
        addMotorDirectionCombinations(motorsUsedMask);
    }
}


void LearningBehavior::addMotorDirectionCombinations(unsigned int motorsUsedMask)
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


void LearningBehavior::addDurationVariations(unsigned int motorsUsedMask, unsigned int motorDirectionMask)
{
    static std::vector<int> secondsToRun = {2, 4, 6};

    for(int timeToRun : secondsToRun)
    {
        _motorsUsed.push_back(motorsUsedMask);
        _motorDirections.push_back(motorDirectionMask);
        _times_s.push_back(timeToRun);
    }
}


LearningBehavior::~LearningBehavior()
{

}


VehicleCommand LearningBehavior::getCommandToExecute(const State& currentTarget, const State& currentState)
{
    VehicleCommand command;

    if(!isLearningComplete())
    {
        currentMemory = Memory();

        command._motorUsedMask = _motorsUsed[_learningIndex];
        command._directionMask = _motorDirections[_learningIndex];
        command._timeElapsed_s = _times_s[_learningIndex];

        currentMemory._command = command;
        currentMemory._initial = currentState;
    }

    return command;
}


void LearningBehavior::processCommandResults(const State& finalState)
{
    if(!isLearningComplete())
    {
        currentMemory._final = finalState;
        currentMemory._confidence = INITIAL_CONFIDENCE;
        _memories->push_back(currentMemory);

        DATA_LOGGER.recordData("New Memory:\n" + currentMemory.to_str());

        ++_learningIndex;
    }
}
