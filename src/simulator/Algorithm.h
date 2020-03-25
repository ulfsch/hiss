//
// Algorithm.h
//
#ifndef CHISS_ALGORITHM_H
#define CHISS_ALGORITHM_H

#include "common.h"
#include "Car.h"
#include "ControlPanel.h"
#include "Stop.h"
#include <vector>

class Simulator;


class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual void operator()(CarList &cars, ControlPanel&, std::vector<Stop> &result) = 0;
};

#endif //CHISS_ALGORITHM_H
