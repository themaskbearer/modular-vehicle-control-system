/*
 * OperatorFunctions.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: jpollard
 */


#include "OperatorFunctions.h"

#include <cstdio>

string operator+(string str, int i)
{
	char* numstring = new char[12];
	sprintf(numstring, "%d", i);

	str += numstring;

	delete[] numstring;

	return str;
}
