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
    ofstream accelfile;
    ofstream sensefile;
    static queue<string> datalist;
    static queue<string> accellist;
    static queue<string> senselist;

    void InitializeMembers(string FilePath);
    void WriteQueuetoFile();
    void WriteAcceltoFile();
    void WriteSensetoFile();
    std::ostream& writeStringtoStream(std::ostream& streamtowrite, string str);

    void ThreadRoutine();

public:
    DataLogger();
    DataLogger(string FilePath);
    virtual ~DataLogger();

    static void recorddata(string Data);
    static void recordaccel(string data);
    static void recordsense(string data);
};

#endif /* DATALOGGER_H_ */
