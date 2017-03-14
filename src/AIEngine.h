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
        private:
                PathPlanner Navigator;
                StateTracker IMU;
                double Confidence;
                vector<Memory> Memories;
                vector<Motor> Motors;
        
                void ThreadRoutine();
                Memory* getBestMemory(State Target);
                void ExecuteMemory(Memory mem);
        
                float CompareStates(State state1, State state2);
                string LogMemory(Memory mem);

        public:
                AIEngine();
                virtual ~AIEngine();
};

#endif /* AIENGINE_H_ */
