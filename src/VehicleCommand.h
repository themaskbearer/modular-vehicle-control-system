/*
 * VehicleCommand.h
 *
 *  Created on: Sep 21, 2017
 *      Author: jpollard
 */

#ifndef SRC_VEHICLECOMMAND_H_
#define SRC_VEHICLECOMMAND_H_

class VehicleCommand {
public:

    int _motorUsedMask = 0;
    int _directionMask = 0;
    float _timeElapsed_s = 0;
};

#endif /* SRC_VEHICLECOMMAND_H_ */
