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
private:
    void SetValues(std::string Msg, int err);

public:
    Exception();
    Exception(std::string Msg);
    Exception(std::string Msg, int ErrorValue);
    virtual ~Exception();

    std::string Message;
    int errorvalue;
};

#endif /* EXCEPTION_H_ */
