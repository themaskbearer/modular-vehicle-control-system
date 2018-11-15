/*
 * OperatorFunctions.h
 *
 *  Created on: Apr 13, 2012
 *      Author: jpollard
 */

#ifndef OPERATORFUNCTIONS_H_
#define OPERATORFUNCTIONS_H_

#include <string>
using std::string;

string operator+(string str, int i);
string operator+(string str, unsigned int i);
string operator+(string str, float f);

#endif /* OPERATORFUNCTIONS_H_ */
