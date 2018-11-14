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

    State getPose() { return _imu.getCurrentState(); }
    int getNumberOfMotors() { return _motors.size(); }

    void runCommand(const VehicleCommand& command);

    void start() override;
    void stop() override;

private:
    std::vector<Motor> _motors;

    StateTracker _imu;
};

#endif /* SRC_TESTPLATFORM_H_ */
