/*
 * AIEngine.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef AIENGINE_H_
#define AIENGINE_H_

#include "thread/Thread.h"
#include "PathPlanner.h"
#include "StateTracker.h"
#include "Motor.h"

#define CONFIDENCE_LEVEL 50

class AIEngine: public Thread
{
public:
    AIEngine();
    virtual ~AIEngine();

private:
    PathPlanner m_navigator;
    StateTracker m_imu;
    double m_confidence = 0;
    vector<Memory> m_memories;
    vector<Motor> m_Motors;

    void threadRoutine();

    void learnConfiguration();
    void followTargets();

    Memory* getBestMemory(const State& Target);
    void executeMemory(const Memory& mem);

    float compareStates(const State& state1, const State& state2);

    void logMemory(const std::string& title, const Memory& mem);
    void logState(const std::string& title, const State& state);
};

#endif /* AIENGINE_H_ */
