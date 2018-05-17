/*
 * ConfigurationLearner.h
 *
 *  Created on: May 17, 2018
 *      Author: jpollard
 */

#ifndef SRC_CONFIGURATIONLEARNER_H_
#define SRC_CONFIGURATIONLEARNER_H_

#include "MovementController.h"
#include "Memory.h"
#include <vector>

class ConfigurationLearner : public MovementController
{
public:
    ConfigurationLearner(unsigned int numOfMotors, MemoryStorage* memories);
    virtual ~ConfigurationLearner();

    VehicleCommand getCommandToExecute(const State& currentTarget, const State& currentState);
    void processCommandResults(const State& finalState);

    // This will be based of off running through all the configurations once, but should eventually be based on the
    // confidence level
    bool isLearningComplete() { return (m_learningIndex == m_motorsUsed.size()); }

private:
    const float CONFIDENCE_LEVEL = 50;
    const float INITIAL_CONFIDENCE = 50;

    unsigned int m_numOfMotors = 0;

    double m_confidence = 0;

    std::vector<int> m_motorsUsed;
    std::vector<int> m_motorDirections;
    std::vector<int> m_times_s;
    unsigned int m_learningIndex = 0;

    Memory currentMemory;

    void addMotorDirectionCombinations(unsigned int motorsUsedMask);
    void addDurationVariations(unsigned int motorsUsedMask, unsigned int motorDirectionMask);
};

#endif /* SRC_CONFIGURATIONLEARNER_H_ */
