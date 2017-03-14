/*
 * ErrorHandler.h
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include <semaphore.h>

#include <fstream>
#include <string>
#include <queue>

#include "Exceptions.h"
#include "Thread.h"


class ErrorHandler : public Thread
{
public:
    virtual ~ErrorHandler();

    static ErrorHandler* instance() { if(m_instance == nullptr) m_instance = new ErrorHandler(); return m_instance; }

    void initialize(const std::string& filePath);
    void close();

    void recordError(const Exception& e);

private:
    ErrorHandler();
    static ErrorHandler* m_instance;

    bool m_initialized = false;

    sem_t m_access;
    std::ofstream m_errorfile;
    std::queue<Exception> m_errorlist;

    void threadRoutine();

    void writeQueuetoFile();
    std::ostream& writeExecptiontoStream(std::ostream& streamtowrite, const Exception& e);
};

#define ERROR_HANDLER       ErrorHandler::instance()

#endif /* ERRORHANDLER_H_ */
