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


class ErrorLogger : public Thread, public Singleton<ErrorLogger>
{
    friend class Singleton<ErrorLogger>;

public:
    typedef std::unique_ptr<ErrorLogger> Ptr;

    virtual ~ErrorLogger();

    void recordError(const std::string& err);

private:
    ErrorLogger();

    const std::string _logFileName = "errors.log";

    Mutex _access;
    std::ofstream _errorfile;
    std::vector<std::string> _errorlist;

    void threadRoutine();

    void writeQueuetoFile();
    std::ostream& writeToStream(std::ostream& streamtowrite, const std::string& err);
};

#define ERROR_LOGGER       ErrorLogger::instance()

#endif /* ERRORHANDLER_H_ */
