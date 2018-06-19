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

#include "thread/Mutex.h"


class GPIO
{
public:
    GPIO();
    GPIO(const GPIO& old);
    virtual ~GPIO();

    void initialize(std::string gpioNumber);

    void makeInput();
    void makeOutput();
    void setState(int state);
    int readState(); //not implemented yet

private:
    Mutex _access;
    std::string _location;
    std::ofstream _direction;
    std::ofstream _value;
    bool _initialized = false;
    bool _is144 = false;

    void initialize144();
};

#endif /* GPIO_H_ */
