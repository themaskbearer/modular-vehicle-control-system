

#include "PathPlanner.h"
#include "utils/DataLogger.h"
#include <cmath>


PathPlanner::PathPlanner()
{
    State temp;
    m_locations.push_back(temp);

    temp.m_displacement.x = 3;
    m_locations.push_back(temp);

    temp.m_displacement.y = 2;
    m_locations.push_back(temp);

    temp.m_displacement.x = 0;
    m_locations.push_back(temp);

    m_currentTarget = m_locations.begin();
}


PathPlanner::~PathPlanner()
{
}


State PathPlanner::getTarget()
{
    return *m_currentTarget;
}


void PathPlanner::updateTarget(State CurrentState)
{
    State positionerror = CurrentState - *m_currentTarget;
    float err = pow(positionerror.m_displacement.x,2) + pow(positionerror.m_displacement.y, 2) +
            pow(positionerror.m_displacement.z, 2);
    err = sqrt(err);

    if(err < ERROR_THRESHOLD)
        m_currentTarget++;

    if(m_currentTarget == m_locations.end())
        m_currentTarget = m_locations.begin();
}
