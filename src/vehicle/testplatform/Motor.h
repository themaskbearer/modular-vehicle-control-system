/*
 * Motor.h
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Gpio.h"

class Motor
{
public:
    Motor(int directionIO, int enableIO);
    Motor(const Motor &oldMotor);
    virtual ~Motor();

    void on();
    void off();
    void forward();
    void reverse();

private:
    HardwareIO::Ptr _direction;
    HardwareIO::Ptr _enable;

};

#endif /* MOTOR_H_ */
