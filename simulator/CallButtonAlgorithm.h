//
// CallButtonAlgorithm.h.
//
#ifndef CHISS_CALLBUTTONALGORITHM_H
#define CHISS_CALLBUTTONALGORITHM_H

#include "Algorithm.h"

class Building;

class CallButtonAlgorithm : public Algorithm {
public:
    CallButtonAlgorithm();

    virtual void operator()(Building &);
};

#endif //CHISS_CALLBUTTONALGORITHM_H
