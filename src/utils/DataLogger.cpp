/*
 * DataLogger.cpp
 *
 *  Created on: Apr 11, 2012
 *      Author: jpollard
 */


#include "DataLogger.h"
#include "ErrorLogger.h"

#include <iostream>


template<> DataLogger::Ptr Singleton<DataLogger>::_instance = nullptr;


DataLogger::DataLogger()
{
    _dataFile.open(_dataFileName.c_str(), std::istream::app);
    if(!_dataFile.is_open())
    {
        ERROR_LOGGER.logError("Can't open data file log...");
        throw FileOpenFailure(_dataFileName);
    }

    _accelFile.open(_accelFileName.c_str(), std::istream::app);
    if(!_accelFile.is_open())
    {
        ERROR_LOGGER.logError("Can't open accel file log...\n");
        throw FileOpenFailure(_accelFileName);
    }

    _senseFile.open(_senseFileName.c_str(), std::istream::app);
    if(!_senseFile.is_open())
    {
        ERROR_LOGGER.logError("Can't open sense file log...\n");
        throw FileOpenFailure(_senseFileName);
    }

    start();
}


DataLogger::~DataLogger()
{
    stop();

    _dataFile.close();
    _accelFile.close();
    _senseFile.close();
}


void DataLogger::threadRoutine()
{
    while(isRunning())
    {
        writeQueuetoFile(_dataList);
        writeQueuetoFile(_accelList);
        writeQueuetoFile(_senseList);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}


void DataLogger::writeQueuetoFile(std::vector<std::string>& queue)
{
    std::vector<std::string> newData;

    {
        std::lock_guard<std::mutex> guard(_access);
        newData = queue;
        queue.clear();
    }

    for(auto& data : newData)
        writeStringtoStream(_dataFile, data);
}


std::ostream& DataLogger::writeStringtoStream(std::ostream& streamtowrite, std::string str)
{
    streamtowrite << str << std::endl;
    return streamtowrite;
}


void DataLogger::recordData(std::string data)
{
    std::lock_guard<std::mutex> guard(_access);
    _dataList.push_back(data);
}


void DataLogger::recordAccel(string data)
{
    std::lock_guard<std::mutex> guard(_access);
    _accelList.push_back(data);
}


void DataLogger::recordSense(string data)
{
    std::lock_guard<std::mutex> guard(_access);
    _senseList.push_back(data);
}
