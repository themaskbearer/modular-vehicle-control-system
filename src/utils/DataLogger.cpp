/*
 * DataLogger.cpp
 *
 *  Created on: Apr 11, 2012
 *      Author: jpollard
 */

#include "DataLogger.h"
#include "ErrorHandler.h"
#include "thread/LockGuard.h"

#include <iostream>


template<> DataLogger* Singleton<DataLogger>::_instance = nullptr;


DataLogger::DataLogger()
{

}


DataLogger::~DataLogger()
{
    if(_initialized)
        close();
}


void DataLogger::initialize()
{
    _dataFile.open("data.log", std::istream::app);
    if(!_dataFile.is_open())
        ERROR_HANDLER.recordError(Exception("Can't open data file log...\n"));
    else
        _dataFile << "\n\n\nNEW SESSION\n";

    _accelFile.open("accel.dat", std::istream::app);
    if(!_accelFile.is_open())
        ERROR_HANDLER.recordError(Exception("Can't open accel file log...\n"));

    _senseFile.open("sense.dat", std::istream::app);
    if(!_senseFile.is_open())
        ERROR_HANDLER.recordError(Exception("Can't open sense file log...\n"));

    _initialized = true;
}


void DataLogger::close()
{
    _initialized = false;

    _dataFile.close();
    _accelFile.close();
    _senseFile.close();
}


void DataLogger::threadRoutine()
{
    while(true)
    {
        writeQueuetoFile(_dataList);
        writeQueuetoFile(_accelList);
        writeQueuetoFile(_senseList);

        usleep(1000);
    }
}


void DataLogger::writeQueuetoFile(std::vector<std::string>& queue)
{
    std::vector<std::string> newData;

    {
        LockGuard guard(_access);
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
    LockGuard guard(_access);
    _dataList.push_back(data);
}


void DataLogger::recordAccel(string data)
{
    LockGuard guard(_access);
    _accelList.push_back(data);
}


void DataLogger::recordSense(string data)
{
    LockGuard guard(_access);
    _senseList.push_back(data);
}
