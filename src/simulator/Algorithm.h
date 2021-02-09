//
// Algorithm.h
//
#ifndef CHISS_ALGORITHM_H
#define CHISS_ALGORITHM_H

#include "common.h"
#include "Car.h"
#include "ControlPanel.h"
#include "Stop.h"


class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual void operator()(CarList &cars, ControlPanel, StopVector &result) = 0;
};

#endif //CHISS_ALGORITHM_H
