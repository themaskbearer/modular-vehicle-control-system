/*
 * ErrorHandler.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "ErrorHandler.h"

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
    int error = sem_init(&m_access, 0, 1);
    if(error == -1)
        std::cerr << "Failed to open access semaphore for Error Handler\n";

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
    sem_destroy(&m_access);
}


void ErrorHandler::threadRoutine()
{
    while(true)
    {
        if(!m_errorlist.empty())
            writeQueuetoFile();

        usleep(1000);
    }
}


void ErrorHandler::writeQueuetoFile()
{
    if(!sem_wait(&m_access))
    {
        while(!m_errorlist.empty())
        {
            writeExecptiontoStream(m_errorfile, m_errorlist.front());
            m_errorlist.pop();
        }

        sem_post(&m_access);
    }
    else
    {
        std::cerr << "Can't get access to queue to log errors...\n";
    }
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
    if(!sem_wait(&m_access))
    {
        m_errorlist.push(e);
        sem_post(&m_access);
    }
    else
    {
        std::cerr << "Can't get access to queue to give error...\n";
    }
}
