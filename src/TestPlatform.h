/*
 * TestPlatform.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jpollard
 */

#ifndef SRC_TESTPLATFORM_H_
#define SRC_TESTPLATFORM_H_

#include "Vehicle.h"
#include "StateTracker.h"
#include "Motor.h"

class TestPlatform : public Vehicle
{
public:
    TestPlatform();
    virtual ~TestPlatform();

    State getPose() { return m_imu.getCurrentState(); }
    int getNumberOfMotors() { return m_motors.size(); }

    void runCommand(const VehicleCommand& command);

    void start();

private:
    std::vector<Motor> m_motors;

    StateTracker m_imu;
};

#endif /* SRC_TESTPLATFORM_H_ */
