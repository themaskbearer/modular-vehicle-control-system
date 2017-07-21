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
public:
    virtual ~SystemGPIOs();

    static SystemGPIOs* instance() { if(m_instance == nullptr) m_instance = new SystemGPIOs(); return m_instance; }
    GPIO* getGPIO(int gpioNumber);

private:
    SystemGPIOs();

    static SystemGPIOs* m_instance;

    map<int, GPIO> GPIOS;
};

#define SYSTEM_GPIOS        SystemGPIOs::instance()

#endif /* SYSTEMGPIOS_H_ */
