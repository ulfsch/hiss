//
// CallButtonAlgorithm.h.
//
#ifndef CHISS_CALLBUTTONALGORITHM_H
#define CHISS_CALLBUTTONALGORITHM_H

#include "Algorithm.h"


class CallButtonAlgorithm : public Algorithm
{
public:
    CallButtonAlgorithm();

    void operator()(Building *, std::vector<Stop>& result) override;

};

#endif //CHISS_CALLBUTTONALGORITHM_H
