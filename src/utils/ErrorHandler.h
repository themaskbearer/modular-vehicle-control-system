/*
 * ErrorHandler.h
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include <fstream>
#include <string>
#include <queue>

#include "Exceptions.h"
#include "thread/Thread.h"
#include "thread/Mutex.h"


class ErrorHandler : public Thread
{
public:
    virtual ~ErrorHandler();

    static ErrorHandler* instance() { if(_instance == nullptr) _instance = new ErrorHandler(); return _instance; }

    void initialize(const std::string& filePath);
    void close();

    void recordError(const Exception& e);

private:
    ErrorHandler();
    static ErrorHandler* _instance;

    bool _initialized = false;

    Mutex _access;
    std::ofstream _errorfile;
    std::vector<Exception> _errorlist;

    void threadRoutine();

    void writeQueuetoFile();
    std::ostream& writeExecptiontoStream(std::ostream& streamtowrite, const Exception& e);
};

#define ERROR_HANDLER       ErrorHandler::instance()

#endif /* ERRORHANDLER_H_ */
