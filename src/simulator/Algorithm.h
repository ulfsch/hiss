//
// Algorithm.h
//
#ifndef CHISS_ALGORITHM_H
#define CHISS_ALGORITHM_H

class Building;

class Algorithm {
public:
    virtual ~Algorithm() = default;
    virtual void operator()(Building&) = 0;
};

#endif //CHISS_ALGORITHM_H
