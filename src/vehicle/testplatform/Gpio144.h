/*
 * Gpio144.h
 *
 *  Created on: Sep 27, 2018
 *      Author: jpollard
 */

#ifndef GPIO144_H_
#define GPIO144_H_

#include "HardwareIO.h"
#include "HardwareIOFile.h"

#include <string>
#include <mutex>

class Gpio144 : public HardwareIO
{
public:
    Gpio144();
    virtual ~Gpio144();

    void makeInput() override;
    void makeOutput() override;
    void setState(int state) override;
    int readState() override; //not implemented yet

private:
    const std::string _path = "/sys/class/gpio/gpio144/value";

    std::mutex _lock;
    HardwareIOFile _value;
};

#endif /* GPIO144_H_ */
