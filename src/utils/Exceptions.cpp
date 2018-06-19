/*
 * Exception.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "Exceptions.h"


Exception::Exception(std::string msg) :
        _message(msg),
        _errorValue(0)
{
}


Exception::Exception(std::string msg, int errorValue) :
        _message(msg),
        _errorValue(errorValue)
{
}


Exception::~Exception()
{

}
