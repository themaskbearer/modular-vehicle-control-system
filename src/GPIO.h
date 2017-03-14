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
using std::ofstream;
using std::string;


class GPIO
{
private:
    sem_t Access;
    string location;
    ofstream direction;
    ofstream value;
    bool Initialized;
    bool is144;

    void Initialize144();

public:
    GPIO();
    GPIO(const GPIO& Old); //This creates just an empty GPIO. Since these carry streams, they cannot be copied
    virtual ~GPIO();
    void Initialize(string gpionumber);
    void makeInput();
    void makeOutput();
    void setState(int state);
    int readState(); //not implemented yet
};

#endif /* GPIO_H_ */
