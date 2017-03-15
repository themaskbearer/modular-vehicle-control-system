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

struct AxesProjection
{
    float x = 0;
    float y = 0;
    float z = 0;
};

struct RotProjection
{
    float roll = 0;
    float pitch = 0;
    float yaw = 0;
};

struct State
{
    AxesProjection m_displacement;
    AxesProjection m_velocity;
    AxesProjection m_acceleration;

    RotProjection m_angPosition;
    RotProjection m_angVelocity;
    RotProjection m_angAcceleration;
};

class Memory
{
public:
    Memory();
    virtual ~Memory();

    State m_initial;
    State m_final;

    int m_motorUsedMask;
    int m_direction;
    float m_timeElapsed_s;

    float m_confidence;
};

istream &operator>>(istream &strm, Memory mem);
ostream &operator<<(ostream &strm, Memory mem);

State operator-(State a, State b);

#endif /* MEMORY_H_ */
