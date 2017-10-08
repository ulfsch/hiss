//
// CallButtonAlgorithm.h.
//
#ifndef CHISS_CALLBUTTONALGORITHM_H
#define CHISS_CALLBUTTONALGORITHM_H

#include "Algorithm.h"


class CallButtonAlgorithm : public Algorithm {
public:
    CallButtonAlgorithm();
    virtual void operator()(Building &) override;

};

#endif //CHISS_CALLBUTTONALGORITHM_H
