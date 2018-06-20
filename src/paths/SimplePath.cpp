/*
 * SimplePath.cpp
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#include "SimplePath.h"
#include <cmath>


SimplePath::SimplePath()
{
    State temp;
    _locations.push_back(temp);

    temp._displacement.x = 3;
    _locations.push_back(temp);

    temp._angPosition.yaw = M_PI_2;
    _locations.push_back(temp);

    temp._displacement.y = 2;
    _locations.push_back(temp);

    temp._angPosition.yaw += M_PI_2;
    _locations.push_back(temp);

    temp._displacement.x = 0;
    _locations.push_back(temp);

    temp._angPosition.yaw += M_PI_2;
    _locations.push_back(temp);

    temp._displacement.y = 0;
    _locations.push_back(temp);

    _currentTarget = _locations.front();
    _currentLocation = _locations.begin();
}


SimplePath::~SimplePath()
{
    // TODO Auto-generated destructor stub
}


void SimplePath::updateTarget(const State& currentState)
{
    State positionerror = _currentTarget - currentState;
    float err = pow(positionerror._displacement.x,2) +
                pow(positionerror._displacement.y, 2) +
                pow(positionerror._displacement.z, 2) +
                pow(positionerror._angPosition.roll, 2) +
                pow(positionerror._angPosition.pitch, 2) +
                pow(positionerror._angPosition.yaw, 2);
    err = sqrt(err);

    if(err < ERROR_THRESHOLD)
    {
        _currentLocation++;

        if(_currentLocation == _locations.end())
            _currentLocation = _locations.begin();

        _currentTarget = *_currentLocation;
    }
}
