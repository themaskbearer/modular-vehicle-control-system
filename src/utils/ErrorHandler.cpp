/*
 * ErrorHandler.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "ErrorHandler.h"
#include "thread/LockGuard.h"

#include <iostream>


ErrorHandler* ErrorHandler::m_instance = nullptr;


ErrorHandler::ErrorHandler()
{
}


ErrorHandler::~ErrorHandler()
{
    if(m_initialized)
        close();
}


void ErrorHandler::initialize(const std::string& filePath)
{
    m_errorfile.open(filePath.c_str(), std::istream::app);
    if(!m_errorfile.is_open())
        std::cerr << "Can't open error file log...\n";
    else
        m_errorfile << "\n\n\nNEW SESSION\n";

    m_initialized = true;
}


void ErrorHandler::close()
{
    m_initialized = false;

    m_errorfile.close();
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
        LockGuard guard(m_access);
        newErrors = m_errorlist;
        m_errorlist.clear();
    }

    for(auto& error : newErrors)
        writeExecptiontoStream(m_errorfile, error);
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
    LockGuard guard(m_access);
    m_errorlist.push_back(e);
}
