/*
 * Memory.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "vehicle/State.h"
#include "vehicle/VehicleCommand.h"

#include <string>
#include <fstream>
#include <vector>

using std::istream;
using std::ostream;

class Memory
{
public:
    Memory();
    ~Memory();

    State _initial;
    State _final;

    VehicleCommand _command;

    float _confidence;

    std::string to_str();
};

istream &operator>>(istream &strm, Memory mem);
ostream &operator<<(ostream &strm, Memory mem);

typedef std::vector<Memory> MemoryStorage;

#endif /* MEMORY_H_ */
