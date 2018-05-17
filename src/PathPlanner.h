
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

    State getTarget();
    void updateTarget(State CurrentState);

private:
    const float ERROR_THRESHOLD = 0.2;

    vector<State> m_locations;
    vector<State>::iterator m_currentTarget;
};

#endif //PATHPLANNER
