
#ifndef PATHPLANNER
#define PATHPLANNER

#include "Memory.h"

#include <vector>;
using std::vector;
using std::iterator;

class PathPlanner
{
private:
	vector<State> Locations;
	iterator<vector<State>> CurrentTarget;

public:
	PathPlanner(void);
	~PathPlanner(void);

	State GetTarget();
	void UpdateTarget(State CurrentState);
};

#endif //PATHPLANNER