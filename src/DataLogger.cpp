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

	datafile.open(FilePath.c_str());
	if(!datafile.is_open())
		ErrorHandler::recorderror(Exception("Can't open data file log...\n"));
}

DataLogger::~DataLogger()
{
	datafile.close();
	sem_destroy(&Access);
}

void DataLogger::ThreadRoutine()
{
	while(true)
	{
		if(!datalist.empty())
			WriteQueuetoFile();

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

