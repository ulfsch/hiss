//
// StandardAlgorithm.h.
//

#ifndef CHISS_STANDARDALGORITHM_H
#define CHISS_STANDARDALGORITHM_H


#include "Algorithm.h"
#include "common.h"
#include <ostream>

class StandardAlgorithm : public Algorithm
{
public:
    virtual void operator()(Building *, std::vector<Stop>& result) override;
};

std::ostream &operator<<(std::ostream &os, Stop &s);

#endif //CHISS_STANDARDALGORITHM_H
