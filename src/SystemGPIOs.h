/*
 * SystemGPIOs.h
 *
 * Created on: Sep 7, 2012
 *
Author: jpollard
 */

#ifndef SYSTEMGPIOS_H_
#define SYSTEMGPIOS_H_

#include "GPIO.h"
#include <map>

using std::map;
using std::pair;

class SystemGPIOs
{
private:
    static map<int, GPIO> GPIOS;

public:
    SystemGPIOs();
    virtual ~SystemGPIOs();

    static GPIO* GetGPIO(int GPIONumber);
};

#endif /* SYSTEMGPIOS_H_ */
