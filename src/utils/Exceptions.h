/*
 * Exception.h
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include "errno.h"


class Exception
{
public:
    Exception(std::string msg);
    Exception(std::string msg, int errorValue);
    virtual ~Exception();

    const std::string& getMessage() const { return _message; }
    int getErrorValue() const { return _errorValue; }

private:
    std::string _message;
    int _errorValue;
};

#endif /* EXCEPTION_H_ */
