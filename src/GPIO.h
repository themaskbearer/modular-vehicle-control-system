/*
 * GPIO.h
 *
 *  Created on: Mar 24, 2012
 *      Author: jpollard
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <semaphore.h>

#include <string>
#include <fstream>



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
    sem_t m_access;
    std::string m_location;
    std::ofstream m_direction;
    std::ofstream m_value;
    bool m_initialized;
    bool m_is144;

    void initialize144();
};

#endif /* GPIO_H_ */
