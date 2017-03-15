/*
 * Memory.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "Memory.h"
#include "utils/Exceptions.h"


Memory::Memory() :
        m_motorUsedMask(0),
        m_direction(0),
        m_timeElapsed_s(0),
        m_confidence(0)
{
}


Memory::~Memory()
{
}


istream &operator>>(istream &strm, Memory mem)
{
    char memstart;

    strm >> memstart;

    if(memstart != 0xFF)
        throw Exception("Incorrect header for memory", memstart);

    strm >> mem.m_initial.m_displacement.x;
    strm >> mem.m_initial.m_displacement.y;
    strm >> mem.m_initial.m_displacement.z;

    strm >> mem.m_initial.m_velocity.x;
    strm >> mem.m_initial.m_velocity.y;
    strm >> mem.m_initial.m_velocity.z;

    strm >> mem.m_initial.m_acceleration.x;
    strm >> mem.m_initial.m_acceleration.y;
    strm >> mem.m_initial.m_acceleration.z;

    strm >> mem.m_initial.m_angPosition.roll;
    strm >> mem.m_initial.m_angPosition.pitch;
    strm >> mem.m_initial.m_angPosition.yaw;

    strm >> mem.m_initial.m_angVelocity.roll;
    strm >> mem.m_initial.m_angVelocity.pitch;
    strm >> mem.m_initial.m_angVelocity.yaw;

    strm >> mem.m_initial.m_angAcceleration.roll;
    strm >> mem.m_initial.m_angAcceleration.pitch;
    strm >> mem.m_initial.m_angAcceleration.yaw;

    strm >> mem.m_motorUsedMask;
    strm >> mem.m_timeElapsed_s;

    strm >> mem.m_final.m_displacement.x;
    strm >> mem.m_final.m_displacement.y;
    strm >> mem.m_final.m_displacement.z;

    strm >> mem.m_final.m_velocity.x;
    strm >> mem.m_final.m_velocity.y;
    strm >> mem.m_final.m_velocity.z;

    strm >> mem.m_final.m_acceleration.x;
    strm >> mem.m_final.m_acceleration.y;
    strm >> mem.m_final.m_acceleration.z;

    strm >> mem.m_final.m_angPosition.roll;
    strm >> mem.m_final.m_angPosition.pitch;
    strm >> mem.m_final.m_angPosition.yaw;

    strm >> mem.m_final.m_angVelocity.roll;
    strm >> mem.m_final.m_angVelocity.pitch;
    strm >> mem.m_final.m_angVelocity.yaw;

    strm >> mem.m_final.m_angAcceleration.roll;
    strm >> mem.m_final.m_angAcceleration.pitch;
    strm >> mem.m_final.m_angAcceleration.yaw;

    strm >> memstart;

    if(memstart != 0xFF)
        throw Exception("Incorrect footer for memory", memstart);

    return strm;
}


ostream &operator<<(ostream& strm, Memory mem)
{
    strm << 0xFF;
    strm << mem.m_initial.m_displacement.x;
    strm << mem.m_initial.m_displacement.y;
    strm << mem.m_initial.m_displacement.z;

    strm << mem.m_initial.m_velocity.x;
    strm << mem.m_initial.m_velocity.y;
    strm << mem.m_initial.m_velocity.z;

    strm << mem.m_initial.m_acceleration.x;
    strm << mem.m_initial.m_acceleration.y;
    strm << mem.m_initial.m_acceleration.z;

    strm << mem.m_initial.m_angPosition.roll;
    strm << mem.m_initial.m_angPosition.pitch;
    strm << mem.m_initial.m_angPosition.yaw;

    strm << mem.m_initial.m_angVelocity.roll;
    strm << mem.m_initial.m_angVelocity.pitch;
    strm << mem.m_initial.m_angVelocity.yaw;

    strm << mem.m_initial.m_angAcceleration.roll;
    strm << mem.m_initial.m_angAcceleration.pitch;
    strm << mem.m_initial.m_angAcceleration.yaw;

    strm << mem.m_motorUsedMask;
    strm << mem.m_timeElapsed_s;

    strm << mem.m_final.m_displacement.x;
    strm << mem.m_final.m_displacement.y;
    strm << mem.m_final.m_displacement.z;

    strm << mem.m_final.m_velocity.x;
    strm << mem.m_final.m_velocity.y;
    strm << mem.m_final.m_velocity.z;

    strm << mem.m_final.m_acceleration.x;
    strm << mem.m_final.m_acceleration.y;
    strm << mem.m_final.m_acceleration.z;

    strm << mem.m_final.m_angPosition.roll;
    strm << mem.m_final.m_angPosition.pitch;
    strm << mem.m_final.m_angPosition.yaw;

    strm << mem.m_final.m_angVelocity.roll;
    strm << mem.m_final.m_angVelocity.pitch;
    strm << mem.m_final.m_angVelocity.yaw;

    strm << mem.m_final.m_angAcceleration.roll;
    strm << mem.m_final.m_angAcceleration.pitch;
    strm << mem.m_final.m_angAcceleration.yaw;
    strm << 0xFF;

    return strm;
}


State operator-(State a, State b)
{
    State ReturnedState;

    ReturnedState.m_acceleration.x = a.m_acceleration.x - b.m_acceleration.x;
    ReturnedState.m_acceleration.y = a.m_acceleration.y - b.m_acceleration.y;
    ReturnedState.m_acceleration.z = a.m_acceleration.z - b.m_acceleration.z;

    ReturnedState.m_velocity.x = a.m_velocity.x - b.m_velocity.x;
    ReturnedState.m_velocity.y = a.m_velocity.y - b.m_velocity.y;
    ReturnedState.m_velocity.z = a.m_velocity.z - b.m_velocity.z;

    ReturnedState.m_displacement.x = a.m_displacement.x - b.m_displacement.x;
    ReturnedState.m_displacement.y = a.m_displacement.y - b.m_displacement.y;
    ReturnedState.m_displacement.z = a.m_displacement.z - b.m_displacement.z;

    ReturnedState.m_angAcceleration.yaw = a.m_angAcceleration.yaw - b.m_angAcceleration.yaw;
    ReturnedState.m_angAcceleration.pitch = a.m_angAcceleration.pitch - b.m_angAcceleration.pitch;
    ReturnedState.m_angAcceleration.roll = a.m_angAcceleration.roll - b.m_angAcceleration.roll;

    ReturnedState.m_angVelocity.yaw = a.m_angVelocity.yaw - b.m_angVelocity.yaw;
    ReturnedState.m_angVelocity.pitch = a.m_angVelocity.pitch - b.m_angVelocity.pitch;
    ReturnedState.m_angVelocity.roll = a.m_angVelocity.roll - b.m_angVelocity.roll;

    ReturnedState.m_angPosition.yaw = a.m_angPosition.yaw - b.m_angPosition.yaw;
    ReturnedState.m_angPosition.pitch = a.m_angPosition.pitch - b.m_angPosition.pitch;
    ReturnedState.m_angPosition.roll = a.m_angPosition.roll - b.m_angPosition.roll;

    return ReturnedState;
}
