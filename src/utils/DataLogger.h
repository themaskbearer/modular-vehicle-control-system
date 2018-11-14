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
#include <stdexcept>
#include <mutex>

#include "utils/Thread.h"
#include "OperatorFunctions.h"
#include "utils/Singleton.h"

class DataLogger : Thread, public Singleton<DataLogger>
{
    friend class Singleton<DataLogger>;

public:
    typedef std::unique_ptr<DataLogger> Ptr;

    virtual ~DataLogger();

    void recordData(std::string data);
    void recordAccel(std::string data);
    void recordSense(std::string data);

private:
    DataLogger();

    const std::string _dataFileName = "data.log";
    const std::string _accelFileName = "accel.dat";
    const std::string _senseFileName = "sense.dat";

    std::mutex _access;
    std::ofstream _dataFile;
    std::ofstream _accelFile;
    std::ofstream _senseFile;
    std::vector<std::string> _dataList;
    std::vector<std::string> _accelList;
    std::vector<std::string> _senseList;

    void writeQueuetoFile(std::vector<std::string>& queue);
    std::ostream& writeStringtoStream(std::ostream& streamtowrite, std::string str);

    void threadRoutine();
};


#define DATA_LOGGER     DataLogger::instance()

#endif /* DATALOGGER_H_ */
