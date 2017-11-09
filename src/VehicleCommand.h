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

    int m_motorUsedMask = 0;
    int m_directionMask = 0;
    float m_timeElapsed_s = 0;
};

#endif /* SRC_VEHICLECOMMAND_H_ */
