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
#include <memory>

#include "thread/Mutex.h"


class Gpio
{
public:
    typedef std::shared_ptr<Gpio> Ptr;

    explicit Gpio(unsigned int gpioNumber);
    Gpio(const Gpio& old) =delete;
    virtual ~Gpio();
    Gpio& operator=(const Gpio& old) =delete;

    void makeInput();
    void makeOutput();
    void setState(int state);
    int readState(); //not implemented yet

private:
    Mutex _access;
    std::string _location;
    std::ofstream _direction;
    std::ofstream _value;
    bool _is144 = false;

    void initialize144();
};

#endif /* GPIO_H_ */
