

#include "PathPlanner.h"
#include "DataLogger.h"
#include <cmath>


PathPlanner::PathPlanner()
{
    Locations.clear();

    State temp = getEmptyState();
    Locations.push_back(temp);

    temp.Displacement.x = 3;
    Locations.push_back(temp);

    temp.Displacement.y = 2;
    Locations.push_back(temp);

    temp.Displacement.x = 0;
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
    float err = pow(positionerror.Displacement.x,2) + pow(positionerror.Displacement.y, 2) +
            pow(positionerror.Displacement.z, 2);
    err = sqrt(err);

    if(err < 0.2)
        CurrentTarget++;

    if(CurrentTarget == Locations.end())
        CurrentTarget = Locations.begin();
}
