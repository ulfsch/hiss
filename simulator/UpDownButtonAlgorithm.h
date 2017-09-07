//
// UpDownButtonAlgorithm.h.
//

#ifndef CHISS_UPDOWNBUTTONALGORITHM_H
#define CHISS_UPDOWNBUTTONALGORITHM_H


#include "Algorithm.h"
#include "../model/common.h"
#include "../model/Elevator.h"
#include "../model/Floor.h"
#include <ostream>

class UpDownButtonAlgorithm : public Algorithm {
public:
    virtual void operator()(Building &);

    struct Stop {
        Stop(FloorNumber n, Direction d = Direction::NONE) : floor(n), direction(d) {}

        FloorNumber floor;
        Direction direction;
    };

    class Comp {
    public:
        Comp(FloorNumber n, Direction d) : current_(n), direction_(d) {}

        bool operator()(const Stop &a, const Stop &b);

    private:
        FloorNumber current_;
        Direction direction_;
    };

};

std::ostream &operator<<(std::ostream &os, UpDownButtonAlgorithm::Stop &s);


#endif //CHISS_UPDOWNBUTTONALGORITHM_H
