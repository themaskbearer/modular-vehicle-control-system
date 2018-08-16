/*
 * ErrorHandler.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "ErrorLogger.h"
#include "thread/LockGuard.h"

#include <iostream>


template<> ErrorLogger::Ptr Singleton<ErrorLogger>::_instance = nullptr;


ErrorLogger::ErrorLogger()
{
    _errorfile.open(logFileName_.c_str(), std::istream::app);
    if(!_errorfile.is_open()) {
        std::cerr << "Can't open error file log...\n";
        throw FileOpenFailure(logFileName_);
    }

    _errorfile << "\n\n\nNEW SESSION\n";
}


ErrorLogger::~ErrorLogger()
{
    _errorfile.close();
}


void ErrorLogger::threadRoutine()
{
    while(true)
    {
        writeQueuetoFile();

        usleep(1000);
    }
}


void ErrorLogger::writeQueuetoFile()
{
    std::vector<std::string> newErrors;

    {
        LockGuard guard(_access);
        newErrors = _errorlist;
        _errorlist.clear();
    }

    for(auto& error : newErrors)
        writeToStream(_errorfile, error);
}


std::ostream& ErrorLogger::writeToStream(std::ostream& streamtowrite, const std::string& err)
{
    streamtowrite << err << std::endl;

    return streamtowrite;
}


void ErrorLogger::recordError(const std::string& err)
{
    LockGuard guard(_access);
    _errorlist.push_back(err);
}
