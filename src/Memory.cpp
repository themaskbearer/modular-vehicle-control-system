/*
 * Memory.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "Memory.h"
#include "utils/Exceptions.h"


Memory::Memory() :
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

    strm >> mem.m_command.m_motorUsedMask;
    strm >> mem.m_command.m_timeElapsed_s;

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

    strm << mem.m_command.m_motorUsedMask;
    strm << mem.m_command.m_timeElapsed_s;

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
