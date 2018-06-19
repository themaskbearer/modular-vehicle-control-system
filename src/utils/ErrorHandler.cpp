/*
 * ErrorHandler.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "ErrorHandler.h"
#include "thread/LockGuard.h"

#include <iostream>


ErrorHandler* ErrorHandler::_instance = nullptr;


ErrorHandler::ErrorHandler()
{
}


ErrorHandler::~ErrorHandler()
{
    if(_initialized)
        close();
}


void ErrorHandler::initialize(const std::string& filePath)
{
    _errorfile.open(filePath.c_str(), std::istream::app);
    if(!_errorfile.is_open())
        std::cerr << "Can't open error file log...\n";
    else
        _errorfile << "\n\n\nNEW SESSION\n";

    _initialized = true;
}


void ErrorHandler::close()
{
    _initialized = false;

    _errorfile.close();
}


void ErrorHandler::threadRoutine()
{
    while(true)
    {
        writeQueuetoFile();

        usleep(1000);
    }
}


void ErrorHandler::writeQueuetoFile()
{
    std::vector<Exception> newErrors;

    {
        LockGuard guard(_access);
        newErrors = _errorlist;
        _errorlist.clear();
    }

    for(auto& error : newErrors)
        writeExecptiontoStream(_errorfile, error);
}


std::ostream& ErrorHandler::writeExecptiontoStream(std::ostream& streamtowrite, const Exception& e)
{
    streamtowrite << e.getMessage();
    if(e.getErrorValue() != 0)
        streamtowrite << " error value: " << e.getErrorValue();
    streamtowrite << std::endl;

    return streamtowrite;
}


void ErrorHandler::recordError(const Exception& e)
{
    LockGuard guard(_access);
    _errorlist.push_back(e);
}
