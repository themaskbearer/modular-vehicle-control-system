/*
 * Motor.h
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "GPIO.h"

class Motor
{
private:
	GPIO direction;
	GPIO enable;

public:
	Motor(string directionIO, string enableIO);
	virtual ~Motor();
	void On();
	void Off();
	void Forward();
	void Reverse();
};

#endif /* MOTOR_H_ */
