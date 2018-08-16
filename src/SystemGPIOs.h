/*
 * SystemGPIOs.h
 *
 * Created on: Sep 7, 2012
 *
Author: jpollard
 */

#ifndef SYSTEMGPIOS_H_
#define SYSTEMGPIOS_H_

#include "utils/Singleton.h"
#include "Gpio.h"
#include <map>

using std::map;
using std::pair;

class SystemGPIOs : public Singleton<SystemGPIOs>
{
    friend class Singleton<SystemGPIOs>;

public:
    typedef std::unique_ptr<SystemGPIOs> Ptr;

    virtual ~SystemGPIOs();

    Gpio::Ptr getGPIO(int gpioNumber);

private:
    SystemGPIOs();

    map<int, Gpio::Ptr> GPIOS;
};

#define SYSTEM_GPIOS        SystemGPIOs::instance()

#endif /* SYSTEMGPIOS_H_ */
