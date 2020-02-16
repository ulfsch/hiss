//
// Created by ulf on 8/20/19.
//

#ifndef CHISS_EVALALGORITHM_H
#define CHISS_EVALALGORITHM_H


#include <common.h>
#include <Algorithm.h>
#include <Direction.h>

class EvalAlgorithm  : public Algorithm
{
public:
    void operator()(Simulator *, ControlPanel&, std::vector<Stop> &result) override;

};


#endif //CHISS_EVALALGORITHM_H
