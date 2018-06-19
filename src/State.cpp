/*
 * State.cpp
 *
 *  Created on: Sep 21, 2017
 *      Author: jpollard
 */

#include "State.h"

State operator-(State a, State b)
{
    State ReturnedState;

    ReturnedState._acceleration.x = a._acceleration.x - b._acceleration.x;
    ReturnedState._acceleration.y = a._acceleration.y - b._acceleration.y;
    ReturnedState._acceleration.z = a._acceleration.z - b._acceleration.z;

    ReturnedState._velocity.x = a._velocity.x - b._velocity.x;
    ReturnedState._velocity.y = a._velocity.y - b._velocity.y;
    ReturnedState._velocity.z = a._velocity.z - b._velocity.z;

    ReturnedState._displacement.x = a._displacement.x - b._displacement.x;
    ReturnedState._displacement.y = a._displacement.y - b._displacement.y;
    ReturnedState._displacement.z = a._displacement.z - b._displacement.z;

    ReturnedState._angAcceleration.yaw = a._angAcceleration.yaw - b._angAcceleration.yaw;
    ReturnedState._angAcceleration.pitch = a._angAcceleration.pitch - b._angAcceleration.pitch;
    ReturnedState._angAcceleration.roll = a._angAcceleration.roll - b._angAcceleration.roll;

    ReturnedState._angVelocity.yaw = a._angVelocity.yaw - b._angVelocity.yaw;
    ReturnedState._angVelocity.pitch = a._angVelocity.pitch - b._angVelocity.pitch;
    ReturnedState._angVelocity.roll = a._angVelocity.roll - b._angVelocity.roll;

    ReturnedState._angPosition.yaw = a._angPosition.yaw - b._angPosition.yaw;
    ReturnedState._angPosition.pitch = a._angPosition.pitch - b._angPosition.pitch;
    ReturnedState._angPosition.roll = a._angPosition.roll - b._angPosition.roll;

    return ReturnedState;
}


