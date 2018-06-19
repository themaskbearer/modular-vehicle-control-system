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
        _confidence(0)
{
}


Memory::~Memory()
{
}


std::string Memory::to_str()
{
    State diff = _final - _initial;

    std::string str = std::string() + _command._motorUsedMask + " " + _command._directionMask + " " + _command._timeElapsed_s + " " + _confidence + " "
            + diff._displacement.x + " " + diff._displacement.y + " " + diff._displacement.z + " " + diff._angPosition.roll + " "
            + diff._angPosition.pitch + " " + diff._angPosition.yaw;

    return str;
}


istream &operator>>(istream &strm, Memory mem)
{
    char memstart;

    strm >> memstart;

    if(memstart != 0xFF)
        throw Exception("Incorrect header for memory", memstart);

    strm >> mem._initial._displacement.x;
    strm >> mem._initial._displacement.y;
    strm >> mem._initial._displacement.z;

    strm >> mem._initial._velocity.x;
    strm >> mem._initial._velocity.y;
    strm >> mem._initial._velocity.z;

    strm >> mem._initial._acceleration.x;
    strm >> mem._initial._acceleration.y;
    strm >> mem._initial._acceleration.z;

    strm >> mem._initial._angPosition.roll;
    strm >> mem._initial._angPosition.pitch;
    strm >> mem._initial._angPosition.yaw;

    strm >> mem._initial._angVelocity.roll;
    strm >> mem._initial._angVelocity.pitch;
    strm >> mem._initial._angVelocity.yaw;

    strm >> mem._initial._angAcceleration.roll;
    strm >> mem._initial._angAcceleration.pitch;
    strm >> mem._initial._angAcceleration.yaw;

    strm >> mem._command._motorUsedMask;
    strm >> mem._command._timeElapsed_s;

    strm >> mem._final._displacement.x;
    strm >> mem._final._displacement.y;
    strm >> mem._final._displacement.z;

    strm >> mem._final._velocity.x;
    strm >> mem._final._velocity.y;
    strm >> mem._final._velocity.z;

    strm >> mem._final._acceleration.x;
    strm >> mem._final._acceleration.y;
    strm >> mem._final._acceleration.z;

    strm >> mem._final._angPosition.roll;
    strm >> mem._final._angPosition.pitch;
    strm >> mem._final._angPosition.yaw;

    strm >> mem._final._angVelocity.roll;
    strm >> mem._final._angVelocity.pitch;
    strm >> mem._final._angVelocity.yaw;

    strm >> mem._final._angAcceleration.roll;
    strm >> mem._final._angAcceleration.pitch;
    strm >> mem._final._angAcceleration.yaw;

    strm >> memstart;

    if(memstart != 0xFF)
        throw Exception("Incorrect footer for memory", memstart);

    return strm;
}


ostream &operator<<(ostream& strm, Memory mem)
{
    strm << 0xFF;
    strm << mem._initial._displacement.x;
    strm << mem._initial._displacement.y;
    strm << mem._initial._displacement.z;

    strm << mem._initial._velocity.x;
    strm << mem._initial._velocity.y;
    strm << mem._initial._velocity.z;

    strm << mem._initial._acceleration.x;
    strm << mem._initial._acceleration.y;
    strm << mem._initial._acceleration.z;

    strm << mem._initial._angPosition.roll;
    strm << mem._initial._angPosition.pitch;
    strm << mem._initial._angPosition.yaw;

    strm << mem._initial._angVelocity.roll;
    strm << mem._initial._angVelocity.pitch;
    strm << mem._initial._angVelocity.yaw;

    strm << mem._initial._angAcceleration.roll;
    strm << mem._initial._angAcceleration.pitch;
    strm << mem._initial._angAcceleration.yaw;

    strm << mem._command._motorUsedMask;
    strm << mem._command._timeElapsed_s;

    strm << mem._final._displacement.x;
    strm << mem._final._displacement.y;
    strm << mem._final._displacement.z;

    strm << mem._final._velocity.x;
    strm << mem._final._velocity.y;
    strm << mem._final._velocity.z;

    strm << mem._final._acceleration.x;
    strm << mem._final._acceleration.y;
    strm << mem._final._acceleration.z;

    strm << mem._final._angPosition.roll;
    strm << mem._final._angPosition.pitch;
    strm << mem._final._angPosition.yaw;

    strm << mem._final._angVelocity.roll;
    strm << mem._final._angVelocity.pitch;
    strm << mem._final._angVelocity.yaw;

    strm << mem._final._angAcceleration.roll;
    strm << mem._final._angAcceleration.pitch;
    strm << mem._final._angAcceleration.yaw;
    strm << 0xFF;

    return strm;
}
