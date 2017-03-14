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


#include "Exceptions.h"
#include "Thread.h"
#include "OperatorFunctions.h"

class DataLogger : public Thread
{
public:
    virtual ~DataLogger();

    static DataLogger* instance() { if(m_instance == nullptr) m_instance = new DataLogger(); return m_instance; }

    void initialize();
    void close();

    void recordData(std::string data);
    void recordAccel(std::string data);
    void recordSense(std::string data);

private:
    static DataLogger* m_instance;
    DataLogger();

    bool m_initialized = false;

    sem_t m_access;
    std::ofstream m_datafile;
    std::ofstream m_accelfile;
    std::ofstream m_sensefile;
    std::queue<std::string> m_datalist;
    std::queue<std::string> m_accellist;
    std::queue<std::string> m_senselist;

    void writeQueuetoFile();
    void writeAcceltoFile();
    void writeSensetoFile();
    std::ostream& writeStringtoStream(std::ostream& streamtowrite, std::string str);

    void threadRoutine();
};


#define DATA_LOGGER     DataLogger::instance()


#endif /* DATALOGGER_H_ */
