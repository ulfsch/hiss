//
// Created by ulf on 8/20/19.
//

#ifndef CHISS_STANDARDALGORITHM_H
#define CHISS_STANDARDALGORITHM_H


#include <common.h>
#include <Algorithm.h>

class StandardAlgorithm : public Algorithm
{
public:
    void operator()(CarList &cars, ControlPanel , std::vector<Stop> &result) override;

};


#endif //CHISS_STANDARDALGORITHM_H
