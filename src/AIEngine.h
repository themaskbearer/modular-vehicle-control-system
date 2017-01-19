/*
 * AIEngine.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef AIENGINE_H_
#define AIENGINE_H_

#include "Thread.h"

#define CONFIDENCE_LEVEL 50

class AIEngine: public Thread
{
private:

	void ThreadRoutine();
	double Confidence;

public:
	AIEngine();
	virtual ~AIEngine();

};

#endif /* AIENGINE_H_ */
