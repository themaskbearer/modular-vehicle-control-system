/*
 * Exception.h
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <stdexcept>
#include <string>
#include "errno.h"


class Exception : public std::exception
{
public:
    Exception(std::string msg);
    Exception(std::string msg, int errorValue);
    virtual ~Exception();

    const std::string& getMessage() const { return _message; }
    int getErrorValue() const { return _errorValue; }

    const char* what() { return _message.c_str(); }

private:
    std::string _message;
    int _errorValue;
};


class FileOpenFailure : public std::runtime_error
{
public:
    FileOpenFailure(std::string fileName) : std::runtime_error("Failed to open data file " + fileName) {}
};

#endif /* EXCEPTION_H_ */
