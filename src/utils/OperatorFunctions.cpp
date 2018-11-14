/*
 * OperatorFunctions.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: jpollard
 */


#include "OperatorFunctions.h"

#include <cstdio>
#include <sstream>
using std::ostringstream;


string operator+(string str, int i)
{
    ostringstream strm;
    strm << i;

    str += strm.str();

    return str;
}

string operator+(string str, unsigned int i)
{
    const size_t maxLength = 12;
    char converted[maxLength];
    sprintf(converted, "%u", i);
    str += converted;
    return str;
}

string operator+(string str, float f)
{
    ostringstream strm;
    strm << f;

    str += strm.str();

    return str;
}
