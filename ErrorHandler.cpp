/*
 * ErrorHandler.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "ErrorHandler.h"

#include <iostream>
using std::cout;
using std::endl;

queue<Exception> ErrorHandler::errorlist;
sem_t ErrorHandler::Access;

ErrorHandler::ErrorHandler()
{
	InitializeMembers("errorlog.log");
}

ErrorHandler::ErrorHandler(std::string FilePath)
{
	InitializeMembers(FilePath);
}

void ErrorHandler::InitializeMembers(string FilePath)
{
	int error = sem_init(&Access, 0, 1);
	if(error == -1)
		cout << "Failed to open access semaphore for Error Handler\n";

	errorfile.open(FilePath.c_str());
	if(!errorfile.is_open())
		cout << "Can't open error file log...\n";
}

ErrorHandler::~ErrorHandler()
{
	errorfile.close();
	sem_destroy(&Access);
}

void ErrorHandler::ThreadRoutine()
{
	while(true)
	{
		if(!errorlist.empty())
			WriteQueuetoFile();

		usleep(1000);
	}
}

void ErrorHandler::WriteQueuetoFile()
{
	if(!sem_wait(&Access))
	{
		while(!errorlist.empty())
		{
			writeExecptiontoStream(errorfile, errorlist.front());
			errorlist.pop();
		}

		sem_post(&Access);
	}
	else
	{
		cout << "Can't get access to queue to log errors...\n";
	}
}

std::ostream& ErrorHandler::writeExecptiontoStream(std::ostream& streamtowrite, Exception e)
{
	streamtowrite << e.Message;
	if(e.errorvalue != -1)
		streamtowrite << " error value: " << e.errorvalue;
	streamtowrite << endl;

	return streamtowrite;
}

void ErrorHandler::recorderror(Exception e)
{
	if(!sem_wait(&Access))
	{
		errorlist.push(e);
		sem_post(&Access);
	}
	else
	{
		cout << "Can't get access to queue to give error...\n";
	}
}
