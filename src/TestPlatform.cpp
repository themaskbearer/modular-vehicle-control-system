/*
 * TestPlatform.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jpollard
 */

#include "TestPlatform.h"
#include "MotorConstants.h"


TestPlatform::TestPlatform()
{
    m_motors.push_back(Motor(MOTOR1DIR, MOTOR1EN));
    m_motors.push_back(Motor(MOTOR2DIR, MOTOR2EN));
    //Motors.push_back(Motor(MOTOR3DIR, MOTOR3EN));
}


TestPlatform::~TestPlatform()
{

}


void TestPlatform::runCommand(const VehicleCommand& command)
{
    int base = 1;
    for(auto& motor : m_motors)
    {
        if(command.m_motorUsedMask & base)
        {
            if(command.m_directionMask & base)
                motor.forward();
            else
                motor.reverse();

            motor.on();
        }

        base = base << 1;
    }

    usleep(command.m_timeElapsed_s * 1000000);

    for(auto& motor : m_motors)
        motor.off();
}


void TestPlatform::start()
{
    m_imu.startThread();
}
