/*
 * ErrorHandler.h
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include <semaphore.h>

#include <fstream>
#include <string>
#include <queue>
using std::string;
using std::queue;
using std::ofstream;

#include "Exceptions.h"
#include "Thread.h"

class ErrorHandler : public Thread
{
private:
	static sem_t Access;
	ofstream errorfile;
	static queue<Exception> errorlist;

	void InitializeMembers(string FilePath);
	void WriteQueuetoFile();
	std::ostream& writeExecptiontoStream(std::ostream& streamtowrite, Exception e);

	void ThreadRoutine();

public:
	ErrorHandler();
	ErrorHandler(std::string FilePath);
	virtual ~ErrorHandler();

	static void recorderror(Exception e);
};

#endif /* ERRORHANDLER_H_ */
