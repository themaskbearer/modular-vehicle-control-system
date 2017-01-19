/*
 * GPIO.h
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <string>
#include <fstream>
using std::ofstream;
using std::string;

class GPIO
{
private:
	string location;
	ofstream direction;
	ofstream value;

public:
	GPIO();
	virtual ~GPIO();
	void Initialize(string gpionumber);
	void makeInput();
	void makeOutput();
	void setState(int state);
	int readState();			//not implemented yet
};

#endif /* GPIO_H_ */
