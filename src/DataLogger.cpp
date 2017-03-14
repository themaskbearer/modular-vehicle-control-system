/*
 * DataLogger.cpp
 *
 *  Created on: Apr 11, 2012
 *      Author: jpollard
 */

#include "DataLogger.h"
#include "ErrorHandler.h"

#include <iostream>
using std::cout;
using std::endl;

queue<string> DataLogger::datalist;
queue<string> DataLogger::accellist;
queue<string> DataLogger::senselist;
sem_t DataLogger::Access;

DataLogger::DataLogger()
{
    InitializeMembers("datalog.log");
}


DataLogger::DataLogger(std::string FilePath)
{
    InitializeMembers(FilePath);
}


void DataLogger::InitializeMembers(string FilePath)
{
    int error = sem_init(&Access, 0, 1);
    if(error == -1)
        ErrorHandler::recorderror(Exception("Can't initialize semaphore for data logger..."));

    datafile.open(FilePath.c_str(), std::istream::app);
    if(!datafile.is_open())
        ErrorHandler::recorderror(Exception("Can't open data file log...\n"));
    else
        datafile << endl << endl << endl << "NEW SESSION" << endl;

    accelfile.open("accel.dat", std::istream::app);
    if(!accelfile.is_open())
        ErrorHandler::recorderror(Exception("Can't open accel file log...\n"));

    sensefile.open("sense.dat", std::istream::app);
    if(!sensefile.is_open())
        ErrorHandler::recorderror(Exception("Can't open sense file log...\n"));
}


DataLogger::~DataLogger()
{
    datafile.close();
    accelfile.close();
    sensefile.close();
    sem_destroy(&Access);
}


void DataLogger::ThreadRoutine()
{
    while(true)
    {
        if(!datalist.empty())
            WriteQueuetoFile();
        if(!accellist.empty())
            WriteAcceltoFile();
        if(!senselist.empty())
            WriteSensetoFile();

        usleep(1000);
    }
}


void DataLogger::WriteQueuetoFile()
{
    if(!sem_wait(&Access))
    {
        while(!datalist.empty())
        {
            writeStringtoStream(datafile, datalist.front());
            datalist.pop();
        }

        sem_post(&Access);
    }
    else
    {
        ErrorHandler::recorderror(Exception("Can't get access to queue to log data...\n"));
    }
}


void DataLogger::WriteAcceltoFile()
{
    if(!sem_wait(&Access))
    {
        while(!accellist.empty())
        {
            writeStringtoStream(accelfile, accellist.front());
            accellist.pop();
        }

        sem_post(&Access);
    }
}


void DataLogger::WriteSensetoFile()
{
    if(!sem_wait(&Access))
    {
        while(!senselist.empty())
        {
            writeStringtoStream(sensefile, senselist.front());
            senselist.pop();
        }

        sem_post(&Access);
    }
}


std::ostream& DataLogger::writeStringtoStream(std::ostream& streamtowrite, string str)
{
    streamtowrite << str << endl;
    return streamtowrite;
}


void DataLogger::recorddata(string Data)
{
    if(!sem_wait(&Access))
    {
        datalist.push(Data);
        sem_post(&Access);
    }
    else
    {
        ErrorHandler::recorderror(Exception("Can't get access to queue to give data...\n"));
    }
}


void DataLogger::recordaccel(string data)
{
    if(!sem_wait(&Access))
    {
        accellist.push(data);
        sem_post(&Access);
    }
    else
    {
        ErrorHandler::recorderror(Exception("Can't get access to queue to give accel...\n"));
    }
}


void DataLogger::recordsense(string data)
{
    if(!sem_wait(&Access))
    {
        senselist.push(data);
        sem_post(&Access);
    }
    else
    {
        ErrorHandler::recorderror(Exception("Can't get access to queue to give sense...\n"));
    }
}
