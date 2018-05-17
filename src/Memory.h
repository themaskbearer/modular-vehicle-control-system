/*
 * Memory.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "State.h"
#include "VehicleCommand.h"

#include <string>
#include <fstream>
using std::istream;
using std::ostream;

class Memory
{
public:
    Memory();
    ~Memory();

    State m_initial;
    State m_final;

    VehicleCommand m_command;

    float m_confidence;

    std::string to_str();
};

istream &operator>>(istream &strm, Memory mem);
ostream &operator<<(ostream &strm, Memory mem);

#endif /* MEMORY_H_ */
