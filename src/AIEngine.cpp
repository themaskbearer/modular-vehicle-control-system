/*
 * AIEngine.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "AIEngine.h"

AIEngine::AIEngine()
{
	// TODO Auto-generated constructor stub

}

AIEngine::~AIEngine()
{
	// TODO Auto-generated destructor stub
}

void AIEngine::ThreadRoutine()
{
	if(Confidence < CONFIDENCE_LEVEL)
	{
		//learning phase
	}

	//driving phase
	while(1)
	{
		//get next point from path planner
		//calculate difference between current orientation and goal
		//search memories for action that optimizes acceleration (for now)
		//predict result
		//drive
		//observe
		//adjust confidence in memory

		usleep(100);
	}
}
