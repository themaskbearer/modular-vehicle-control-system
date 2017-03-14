/*
 * Exception.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: jpollard
 */

#include "Exceptions.h"


Exception::Exception(std::string msg) :
        m_message(msg),
        m_errorValue(0)
{
}


Exception::Exception(std::string msg, int errorValue) :
        m_message(msg),
        m_errorValue(errorValue)
{
}


Exception::~Exception()
{

}
