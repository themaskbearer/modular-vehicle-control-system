/*
 * Memory.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "Memory.h"
#include "utils/Exceptions.h"
#include "utils/OperatorFunctions.h"


Memory::Memory() :
        m_confidence(0)
{
}


Memory::~Memory()
{
}


std::string Memory::to_str()
{
    State diff = m_final - m_initial;

    std::string str = std::string() + m_command.m_motorUsedMask + " " + m_command.m_directionMask + " " + m_command.m_timeElapsed_s + " " + m_confidence + " "
            + diff.m_displacement.x + " " + diff.m_displacement.y + " " + diff.m_displacement.z + " " + diff.m_angPosition.roll + " "
            + diff.m_angPosition.pitch + " " + diff.m_angPosition.yaw;

    return str;
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
