//
// TrivialAlgorithm.h.
//
#ifndef CHISS_TRIVIALALGORITHM_H
#define CHISS_TRIVIALALGORITHM_H

#include "Algorithm.h"


class TrivialAlgorithm : public Algorithm
{
public:
    TrivialAlgorithm();

    void operator()(Simulator *, std::vector<Stop> &result) override;

};

#endif //CHISS_TRIVIALALGORITHM_H
