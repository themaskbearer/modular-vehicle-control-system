/*
 * Memory.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "Memory.h"
#include "Exceptions.h"

State getEmptyState()
{
    State returnstate;

    returnstate.Acceleration.x = 0;
    returnstate.Acceleration.y = 0;
    returnstate.Acceleration.z = 0;

    returnstate.Displacement.x = 0;
    returnstate.Displacement.y = 0;
    returnstate.Displacement.z = 0;

    returnstate.Velocity.x = 0;
    returnstate.Velocity.y = 0;
    returnstate.Velocity.z = 0;

    returnstate.RPY.yaw = 0;
    returnstate.RPY.roll = 0;
    returnstate.RPY.pitch = 0;

    return returnstate;
}


Memory::Memory()
{
    Initial = getEmptyState();
    Final = getEmptyState();
    deltaT = 0;
    MotorUsed = 0;
    direction = 0;
    confidence = 0;
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

    strm >> mem.Initial.Displacement.x;
    strm >> mem.Initial.Displacement.y;
    strm >> mem.Initial.Displacement.z;

    strm >> mem.Initial.Velocity.x;
    strm >> mem.Initial.Velocity.y;
    strm >> mem.Initial.Velocity.z;

    strm >> mem.Initial.Acceleration.x;
    strm >> mem.Initial.Acceleration.y;
    strm >> mem.Initial.Acceleration.z;

    strm >> mem.Initial.RPY.roll;
    strm >> mem.Initial.RPY.pitch;
    strm >> mem.Initial.RPY.yaw;

    strm >> mem.Initial.AngVelocity.roll;
    strm >> mem.Initial.AngVelocity.pitch;
    strm >> mem.Initial.AngVelocity.yaw;

    strm >> mem.Initial.AngAcceleration.roll;
    strm >> mem.Initial.AngAcceleration.pitch;
    strm >> mem.Initial.AngAcceleration.yaw;

    strm >> mem.MotorUsed;
    strm >> mem.deltaT;

    strm >> mem.Final.Displacement.x;
    strm >> mem.Final.Displacement.y;
    strm >> mem.Final.Displacement.z;

    strm >> mem.Final.Velocity.x;
    strm >> mem.Final.Velocity.y;
    strm >> mem.Final.Velocity.z;

    strm >> mem.Final.Acceleration.x;
    strm >> mem.Final.Acceleration.y;
    strm >> mem.Final.Acceleration.z;

    strm >> mem.Final.RPY.roll;
    strm >> mem.Final.RPY.pitch;
    strm >> mem.Final.RPY.yaw;

    strm >> mem.Final.AngVelocity.roll;
    strm >> mem.Final.AngVelocity.pitch;
    strm >> mem.Final.AngVelocity.yaw;

    strm >> mem.Final.AngAcceleration.roll;
    strm >> mem.Final.AngAcceleration.pitch;
    strm >> mem.Final.AngAcceleration.yaw;

    strm >> memstart;

    if(memstart != 0xFF)
        throw Exception("Incorrect footer for memory", memstart);

    return strm;
}


ostream &operator<<(ostream& strm, Memory mem)
{
    strm << 0xFF;
    strm << mem.Initial.Displacement.x;
    strm << mem.Initial.Displacement.y;
    strm << mem.Initial.Displacement.z;

    strm << mem.Initial.Velocity.x;
    strm << mem.Initial.Velocity.y;
    strm << mem.Initial.Velocity.z;

    strm << mem.Initial.Acceleration.x;
    strm << mem.Initial.Acceleration.y;
    strm << mem.Initial.Acceleration.z;

    strm << mem.Initial.RPY.roll;
    strm << mem.Initial.RPY.pitch;
    strm << mem.Initial.RPY.yaw;

    strm << mem.Initial.AngVelocity.roll;
    strm << mem.Initial.AngVelocity.pitch;
    strm << mem.Initial.AngVelocity.yaw;

    strm << mem.Initial.AngAcceleration.roll;
    strm << mem.Initial.AngAcceleration.pitch;
    strm << mem.Initial.AngAcceleration.yaw;

    strm << mem.MotorUsed;
    strm << mem.deltaT;

    strm << mem.Final.Displacement.x;
    strm << mem.Final.Displacement.y;
    strm << mem.Final.Displacement.z;

    strm << mem.Final.Velocity.x;
    strm << mem.Final.Velocity.y;
    strm << mem.Final.Velocity.z;

    strm << mem.Final.Acceleration.x;
    strm << mem.Final.Acceleration.y;
    strm << mem.Final.Acceleration.z;

    strm << mem.Final.RPY.roll;
    strm << mem.Final.RPY.pitch;
    strm << mem.Final.RPY.yaw;

    strm << mem.Final.AngVelocity.roll;
    strm << mem.Final.AngVelocity.pitch;
    strm << mem.Final.AngVelocity.yaw;

    strm << mem.Final.AngAcceleration.roll;
    strm << mem.Final.AngAcceleration.pitch;
    strm << mem.Final.AngAcceleration.yaw;
    strm << 0xFF;

    return strm;
}


State operator-(State a, State b)
{
    State ReturnedState;

    ReturnedState.Acceleration.x = a.Acceleration.x - b.Acceleration.x;
    ReturnedState.Acceleration.y = a.Acceleration.y - b.Acceleration.y;
    ReturnedState.Acceleration.z = a.Acceleration.z - b.Acceleration.z;

    ReturnedState.Velocity.x = a.Velocity.x - b.Velocity.x;
    ReturnedState.Velocity.y = a.Velocity.y - b.Velocity.y;
    ReturnedState.Velocity.z = a.Velocity.z - b.Velocity.z;

    ReturnedState.Displacement.x = a.Displacement.x - b.Displacement.x;
    ReturnedState.Displacement.y = a.Displacement.y - b.Displacement.y;
    ReturnedState.Displacement.z = a.Displacement.z - b.Displacement.z;

    ReturnedState.AngAcceleration.yaw = a.AngAcceleration.yaw - b.AngAcceleration.yaw;
    ReturnedState.AngAcceleration.pitch = a.AngAcceleration.pitch - b.AngAcceleration.pitch;
    ReturnedState.AngAcceleration.roll = a.AngAcceleration.roll - b.AngAcceleration.roll;

    ReturnedState.AngVelocity.yaw = a.AngVelocity.yaw - b.AngVelocity.yaw;
    ReturnedState.AngVelocity.pitch = a.AngVelocity.pitch - b.AngVelocity.pitch;
    ReturnedState.AngVelocity.roll = a.AngVelocity.roll - b.AngVelocity.roll;

    ReturnedState.RPY.yaw = a.RPY.yaw - b.RPY.yaw;
    ReturnedState.RPY.pitch = a.RPY.pitch - b.RPY.pitch;
    ReturnedState.RPY.roll = a.RPY.roll - b.RPY.roll;

    return ReturnedState;
}
