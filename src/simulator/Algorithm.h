//
// Algorithm.h
//
#ifndef CHISS_ALGORITHM_H
#define CHISS_ALGORITHM_H

#include "common.h"
#include "Stop.h"
#include <vector>

class Simulator;


class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual void operator()(Simulator *, std::vector<Stop> &result) = 0;
};

#endif //CHISS_ALGORITHM_H
