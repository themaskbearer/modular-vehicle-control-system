/*
 * HardwareIO.h
 *
 *  Created on: Sep 27, 2018
 *      Author: jpollard
 */

#ifndef SRC_UTILS_HARDWAREIO_H_
#define SRC_UTILS_HARDWAREIO_H_

#include <memory>

class HardwareIO
{
public:
    typedef std::shared_ptr<HardwareIO> Ptr;

    virtual ~HardwareIO() {};

    virtual void makeInput() =0;
    virtual void makeOutput() =0;
    virtual void setState(int state) =0;
    virtual int readState() =0;
};

#endif /* SRC_UTILS_HARDWAREIO_H_ */
