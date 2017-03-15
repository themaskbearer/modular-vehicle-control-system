

#include "PathPlanner.h"
#include "utils/DataLogger.h"
#include <cmath>


PathPlanner::PathPlanner()
{
    Locations.clear();

    State temp;
    Locations.push_back(temp);

    temp.m_displacement.x = 3;
    Locations.push_back(temp);

    temp.m_displacement.y = 2;
    Locations.push_back(temp);

    temp.m_displacement.x = 0;
    Locations.push_back(temp);

    CurrentTarget = Locations.begin();
}


PathPlanner::~PathPlanner()
{
}


State PathPlanner::GetTarget()
{
    return *CurrentTarget;
}


void PathPlanner::UpdateTarget(State CurrentState)
{
    State positionerror = CurrentState - *CurrentTarget;
    float err = pow(positionerror.m_displacement.x,2) + pow(positionerror.m_displacement.y, 2) +
            pow(positionerror.m_displacement.z, 2);
    err = sqrt(err);

    if(err < ERROR_THRESHOLD)
        CurrentTarget++;

    if(CurrentTarget == Locations.end())
        CurrentTarget = Locations.begin();
}
