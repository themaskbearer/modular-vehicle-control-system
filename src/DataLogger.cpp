/*
 * DataLogger.cpp
 *
 *  Created on: Apr 11, 2012
 *      Author: jpollard
 */

#include "DataLogger.h"
#include "ErrorHandler.h"

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
    int error = sem_init(&m_access, 0, 1);
    if(error == -1)
        ERROR_HANDLER->recordError(Exception("Can't initialize semaphore for data logger..."));

    m_datafile.open("data.log", std::istream::app);
    if(!m_datafile.is_open())
        ERROR_HANDLER->recordError(Exception("Can't open data file log...\n"));
    else
        m_datafile << "\n\n\nNEW SESSION\n";

    m_accelfile.open("accel.dat", std::istream::app);
    if(!m_accelfile.is_open())
        ERROR_HANDLER->recordError(Exception("Can't open accel file log...\n"));

    m_sensefile.open("sense.dat", std::istream::app);
    if(!m_sensefile.is_open())
        ERROR_HANDLER->recordError(Exception("Can't open sense file log...\n"));

    m_initialized = true;
}


void DataLogger::close()
{
    m_initialized = false;

    m_datafile.close();
    m_accelfile.close();
    m_sensefile.close();
    sem_destroy(&m_access);
}


void DataLogger::threadRoutine()
{
    while(true)
    {
        if(!m_datalist.empty())
            writeQueuetoFile();
        if(!m_accellist.empty())
            writeAcceltoFile();
        if(!m_senselist.empty())
            writeSensetoFile();

        usleep(1000);
    }
}


void DataLogger::writeQueuetoFile()
{
    if(!sem_wait(&m_access))
    {
        while(!m_datalist.empty())
        {
            writeStringtoStream(m_datafile, m_datalist.front());
            m_datalist.pop();
        }

        sem_post(&m_access);
    }
    else
    {
        ERROR_HANDLER->recordError(Exception("Can't get access to queue to log data...\n"));
    }
}


void DataLogger::writeAcceltoFile()
{
    if(!sem_wait(&m_access))
    {
        while(!m_accellist.empty())
        {
            writeStringtoStream(m_accelfile, m_accellist.front());
            m_accellist.pop();
        }

        sem_post(&m_access);
    }
}


void DataLogger::writeSensetoFile()
{
    if(!sem_wait(&m_access))
    {
        while(!m_senselist.empty())
        {
            writeStringtoStream(m_sensefile, m_senselist.front());
            m_senselist.pop();
        }

        sem_post(&m_access);
    }
}


std::ostream& DataLogger::writeStringtoStream(std::ostream& streamtowrite, std::string str)
{
    streamtowrite << str << std::endl;
    return streamtowrite;
}


void DataLogger::recordData(std::string data)
{
    if(!sem_wait(&m_access))
    {
        m_datalist.push(data);
        sem_post(&m_access);
    }
    else
    {
        ERROR_HANDLER->recordError(Exception("Can't get access to queue to give data...\n"));
    }
}


void DataLogger::recordAccel(string data)
{
    if(!sem_wait(&m_access))
    {
        m_accellist.push(data);
        sem_post(&m_access);
    }
    else
    {
        ERROR_HANDLER->recordError(Exception("Can't get access to queue to give accel...\n"));
    }
}


void DataLogger::recordSense(string data)
{
    if(!sem_wait(&m_access))
    {
        m_senselist.push(data);
        sem_post(&m_access);
    }
    else
    {
        ERROR_HANDLER->recordError(Exception("Can't get access to queue to give sense...\n"));
    }
}
