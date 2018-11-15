/*
 * GPIO.h
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "HardwareIO.h"
#include "HardwareIOFile.h"

#include <string>
#include <fstream>
#include <memory>
#include <mutex>


class Gpio : public HardwareIO
{
public:
    typedef std::shared_ptr<Gpio> Ptr;

    explicit Gpio(unsigned int gpioNumber);
    Gpio(const Gpio& old) =delete;
    virtual ~Gpio();
    Gpio& operator=(const Gpio& old) =delete;

    void makeInput() override;
    void makeOutput() override;
    void setState(int state) override;
    int readState() override; //not implemented yet

private:
    const std::string _path = "/sys/class/gpio/gpio";

    std::mutex _access;
    HardwareIOFile _direction;
    HardwareIOFile _value;
};

#endif /* GPIO_H_ */
