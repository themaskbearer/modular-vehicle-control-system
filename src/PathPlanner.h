
#ifndef PATHPLANNER
#define PATHPLANNER

#include "Memory.h"


class PathPlanner
{

public:
    PathPlanner(void) {}
    virtual ~PathPlanner(void) {}

    const State& getTarget() { return _currentTarget; }
    virtual void updateTarget(const State& CurrentState) =0;

protected:
    State _currentTarget;
};

#endif //PATHPLANNER
