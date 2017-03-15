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


DataLogger* DataLogger::m_instance = nullptr;


DataLogger::DataLogger()
{

}


DataLogger::~DataLogger()
{
    if(m_initialized)
        close();
}


void DataLogger::initialize()
{
    m_dataFile.open("data.log", std::istream::app);
    if(!m_dataFile.is_open())
        ERROR_HANDLER->recordError(Exception("Can't open data file log...\n"));
    else
        m_dataFile << "\n\n\nNEW SESSION\n";

    m_accelFile.open("accel.dat", std::istream::app);
    if(!m_accelFile.is_open())
        ERROR_HANDLER->recordError(Exception("Can't open accel file log...\n"));

    m_senseFile.open("sense.dat", std::istream::app);
    if(!m_senseFile.is_open())
        ERROR_HANDLER->recordError(Exception("Can't open sense file log...\n"));

    m_initialized = true;
}


void DataLogger::close()
{
    m_initialized = false;

    m_dataFile.close();
    m_accelFile.close();
    m_senseFile.close();
}


void DataLogger::threadRoutine()
{
    while(true)
    {
        writeQueuetoFile(m_dataList);
        writeQueuetoFile(m_accelList);
        writeQueuetoFile(m_senseList);

        usleep(1000);
    }
}


void DataLogger::writeQueuetoFile(std::vector<std::string>& queue)
{
    std::vector<std::string> newData;

    {
        LockGuard guard(m_access);
        newData = queue;
        queue.clear();
    }

    for(auto& data : newData)
        writeStringtoStream(m_dataFile, data);
}


std::ostream& DataLogger::writeStringtoStream(std::ostream& streamtowrite, std::string str)
{
    streamtowrite << str << std::endl;
    return streamtowrite;
}


void DataLogger::recordData(std::string data)
{
    LockGuard guard(m_access);
    m_dataList.push_back(data);
}


void DataLogger::recordAccel(string data)
{
    LockGuard guard(m_access);
    m_accelList.push_back(data);
}


void DataLogger::recordSense(string data)
{
    LockGuard guard(m_access);
    m_senseList.push_back(data);
}
