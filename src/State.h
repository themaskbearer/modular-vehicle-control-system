/*
 * State.h
 *
 *  Created on: Sep 21, 2017
 *      Author: jpollard
 */

#ifndef SRC_STATE_H_
#define SRC_STATE_H_


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


State operator-(State a, State b);

#endif /* SRC_STATE_H_ */
