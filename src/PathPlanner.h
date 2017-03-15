
#ifndef PATHPLANNER
#define PATHPLANNER

#include "Memory.h"

#include <vector>
using std::vector;
using std::iterator;

class PathPlanner
{

public:
    PathPlanner(void);
    ~PathPlanner(void);

    State GetTarget();
    void UpdateTarget(State CurrentState);

private:
    const float ERROR_THRESHOLD = 0.2;

    vector<State> Locations;
    vector<State>::iterator CurrentTarget;
};

#endif //PATHPLANNER
