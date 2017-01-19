/*
 * Memory.h
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <fstream>
using std::istream;
using std::ostream;

struct axesprojection
{
	float x;
	float y;
	float z;
};

struct rotprojection
{
	float roll;
	float pitch;
	float heading;
};

struct State
{
	axesprojection Displacement;
	axesprojection Velocity;
	axesprojection Acceleration;

	rotprojection HPR;
	rotprojection AngVelocity;
	rotprojection AngAcceleration;
};

State getEmptyState();

class Memory
{
public:
	State Initial;
	State Final;

	int MotorUsed;
	float deltaT;

	Memory();
	virtual ~Memory();
};

istream &operator>>(istream &strm, Memory mem);
ostream &operator<<(ostream &strm, Memory mem);

State operator-(State a, State b);

#endif /* MEMORY_H_ */
