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

    const std::string& getMessage() const { return m_message; }
    int getErrorValue() const { return m_errorValue; }

private:
    std::string m_message;
    int m_errorValue;
};

#endif /* EXCEPTION_H_ */
