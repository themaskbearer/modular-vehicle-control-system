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
    // Since the GPIO are not in the correct state on power on, this allows for final configuration
    // of the vehicle before deployment where the motors aren't turning
    usleep(300000000); // 5 mins

    _motors.push_back(Motor(MOTOR1DIR, MOTOR1EN));
    _motors.push_back(Motor(MOTOR2DIR, MOTOR2EN));
    //Motors.push_back(Motor(MOTOR3DIR, MOTOR3EN));
}


TestPlatform::~TestPlatform()
{

}


void TestPlatform::runCommand(const VehicleCommand& command)
{
    int base = 1;
    for(auto& motor : _motors)
    {
        if(command._motorUsedMask & base)
        {
            if(command._directionMask & base)
                motor.forward();
            else
                motor.reverse();

            motor.on();
        }

        base = base << 1;
    }

    usleep(command._timeElapsed_s * 1000000);

    for(auto& motor : _motors)
        motor.off();
}


void TestPlatform::start()
{
    _imu.startThread();
}
