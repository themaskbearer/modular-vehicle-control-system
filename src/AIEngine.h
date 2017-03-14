/*
 * AIEngine.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef AIENGINE_H_
#define AIENGINE_H_

#include "Thread.h"
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
    double m_confidence;
    vector<Memory> m_memories;
    vector<Motor> m_Motors;

    void threadRoutine();
    Memory* getBestMemory(State Target);
    void executeMemory(Memory mem);

    float compareStates(State state1, State state2);
    string logMemory(Memory mem);
};

#endif /* AIENGINE_H_ */
