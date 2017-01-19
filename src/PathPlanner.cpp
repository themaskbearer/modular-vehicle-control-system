
#include "PathPlanner.h"

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

PathPlanner::PathPlanner()
{
}

State PathPlanner::GetTarget()
{
	return *CurrentTarget;
}

void PathPlanner::UpdateTarget(State CurrentState)
{

}