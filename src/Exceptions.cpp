/*
 * Exception.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "Exceptions.h"

Exception::Exception()
{
    SetValues("", -1);
}


Exception::Exception(std::string Msg)
{
    SetValues(Msg, -1);
}


Exception::Exception(std::string Msg, int ErrorValue)
{
    SetValues(Msg, ErrorValue);
}


void Exception::SetValues(std::string Msg, int err)
{
    Message = Msg;
    errorvalue = err;
}


Exception::~Exception()
{
    // TODO Auto-generated destructor stub
}
