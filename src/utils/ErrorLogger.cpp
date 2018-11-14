/*
 * ErrorHandler.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "ErrorLogger.h"

#include <iostream>


template<> ErrorLogger::Ptr Singleton<ErrorLogger>::_instance = nullptr;


ErrorLogger::ErrorLogger()
{
    _errorfile.open(_logFileName.c_str(), std::istream::app);
    if(!_errorfile.is_open()) {
        std::cerr << "Can't open error file log...\n";
        throw FileOpenFailure(_logFileName);
    }

    start();
}


ErrorLogger::~ErrorLogger()
{
    stop();
    _errorfile.close();
}


void ErrorLogger::threadRoutine()
{
    while(isRunning())
    {
        writeQueuetoFile();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}


void ErrorLogger::writeQueuetoFile()
{
    std::vector<std::string> newErrors;

    {
        std::lock_guard<std::mutex> guard(_access);
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
    std::lock_guard<std::mutex> guard(_access);
    _errorlist.push_back(err);
}
