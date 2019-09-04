//
// Algorithm.h
//
#ifndef CHISS_ALGORITHM_H
#define CHISS_ALGORITHM_H

#include <Stop.h>
#include <vector>

class Building;

class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual void operator()(Building *, std::vector<Stop>& result) = 0;
};

#endif //CHISS_ALGORITHM_H
