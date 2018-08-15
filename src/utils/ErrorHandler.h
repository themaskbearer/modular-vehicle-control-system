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

#include "utils/Singleton.h"
#include "Exceptions.h"
#include "thread/Thread.h"
#include "thread/Mutex.h"


class ErrorHandler : public Thread, public Singleton<ErrorHandler>
{
    friend class Singleton<ErrorHandler>;

public:
    virtual ~ErrorHandler();

    void initialize(const std::string& filePath);
    void close();

    void recordError(const Exception& e);

private:
    ErrorHandler();

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
