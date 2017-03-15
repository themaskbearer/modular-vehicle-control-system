/*
 * DataLogger.h
 *
 *  Created on: Apr 11, 2012
 *      Author: jpollard
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <fstream>
#include <string>
#include <queue>

#include "Exceptions.h"
#include "thread/Thread.h"
#include "thread/Mutex.h"
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

    Mutex m_access;
    std::ofstream m_dataFile;
    std::ofstream m_accelFile;
    std::ofstream m_senseFile;
    std::vector<std::string> m_dataList;
    std::vector<std::string> m_accelList;
    std::vector<std::string> m_senseList;

    void writeQueuetoFile(std::vector<std::string>& queue);
    std::ostream& writeStringtoStream(std::ostream& streamtowrite, std::string str);

    void threadRoutine();
};


#define DATA_LOGGER     DataLogger::instance()


#endif /* DATALOGGER_H_ */
