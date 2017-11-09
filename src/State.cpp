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


