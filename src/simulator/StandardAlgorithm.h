//
// StandardAlgorithm.h.
//

#ifndef CHISS_STANDARDALGORITHM_H
#define CHISS_STANDARDALGORITHM_H

#include "Algorithm.h"


class StandardAlgorithm : public Algorithm
{
public:
    virtual void operator()(Simulator *, std::vector<Stop> &result) override;

};

#endif //CHISS_STANDARDALGORITHM_H
