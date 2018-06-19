

#include "PathPlanner.h"
#include "utils/DataLogger.h"
#include <cmath>


PathPlanner::PathPlanner()
{
    State temp;
    _locations.push_back(temp);

    temp._displacement.x = 3;
    _locations.push_back(temp);

    temp._angPosition.yaw = -M_PI_2;
    _locations.push_back(temp);

    temp._displacement.y = 2;
    _locations.push_back(temp);

    temp._angPosition.yaw -= -M_PI_2;
    _locations.push_back(temp);

    temp._displacement.x = 0;
    _locations.push_back(temp);

    temp._angPosition.yaw -= -M_PI_2;
    _locations.push_back(temp);

    _currentTarget = _locations.begin();
}


PathPlanner::~PathPlanner()
{
}


State PathPlanner::getTarget()
{
    return *_currentTarget;
}


void PathPlanner::updateTarget(State CurrentState)
{
    State positionerror = CurrentState - *_currentTarget;
    float err = pow(positionerror._displacement.x,2) + pow(positionerror._displacement.y, 2) +
            pow(positionerror._displacement.z, 2);
    err = sqrt(err);

    if(err < ERROR_THRESHOLD)
        _currentTarget++;

    if(_currentTarget == _locations.end())
        _currentTarget = _locations.begin();
}
