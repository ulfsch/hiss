//
// UpDownButtonAlgorithm.h.
//

#ifndef CHISS_UPDOWNBUTTONALGORITHM_H
#define CHISS_UPDOWNBUTTONALGORITHM_H


#include "Algorithm.h"
#include "common.h"
#include <ostream>

class UpDownButtonAlgorithm : public Algorithm
{
public:
    virtual void operator()(Building *, std::vector<Stop>& result) override;
};

std::ostream &operator<<(std::ostream &os, Stop &s);

#endif //CHISS_UPDOWNBUTTONALGORITHM_H
