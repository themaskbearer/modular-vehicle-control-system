/*
 * Exception.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "Exceptions.h"

Exception::Exception()
{
	Exception("");
}

Exception::Exception(std::string Msg)
{
	Exception(Msg, -1);
}

Exception::Exception(std::string Msg, int ErrorValue)
{
	Message = Msg;
	errorvalue = ErrorValue;
}

Exception::~Exception()
{
	// TODO Auto-generated destructor stub
}

