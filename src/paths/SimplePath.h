/*
 * SimplePath.h
 *
 *  Created on: Jun 20, 2018
 *      Author: jpollard
 */

#ifndef SRC_SIMPLEPATH_H_
#define SRC_SIMPLEPATH_H_

#include "PathPlanner.h"
#include <vector>


class SimplePath : public PathPlanner
{
public:
    SimplePath();
    virtual ~SimplePath();

    void updateTarget(const State& currentState);

private:
    const float ERROR_THRESHOLD = 0.2;

    std::vector<State> _locations;
    std::vector<State>::iterator _currentLocation;
};

#endif /* SRC_SIMPLEPATH_H_ */
