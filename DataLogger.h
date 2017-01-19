/*
 * DataLogger.h
 *
 *  Created on: Apr 11, 2012
 *      Author: jpollard
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <semaphore.h>

#include <fstream>
#include <string>
#include <queue>
using std::string;
using std::queue;
using std::ofstream;

#include "Exceptions.h"
#include "Thread.h"
#include "OperatorFunctions.h"

class DataLogger : public Thread
{
private:
	static sem_t Access;
	ofstream datafile;
	static queue<string> datalist;

	void InitializeMembers(string FilePath);
	void WriteQueuetoFile();
	std::ostream& writeStringtoStream(std::ostream& streamtowrite, string str);

	void ThreadRoutine();

public:
	DataLogger();
	DataLogger(string FilePath);
	virtual ~DataLogger();

	static void recorddata(string Data);
};

#endif /* DATALOGGER_H_ */
