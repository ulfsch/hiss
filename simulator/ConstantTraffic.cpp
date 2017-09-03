//
// ConstantTraffic.cpp.
//
#include "ConstantTraffic.h"
#include <cstdlib>

ConstantTraffic::ConstantTraffic(size_t number_of_floors,
                                 size_t total_no_of_passengers,
                                 double passengers_per_tick) :
        number_of_floors_(number_of_floors),
        max_no_of_passengers_(total_no_of_passengers),
        passengers_per_tick_(passengers_per_tick),
        no_of_passengers_(0),
        count_(0) {
}

Passenger *ConstantTraffic::operator()(Time time) {
    while (count_ < passengers_per_tick_ &&
           no_of_passengers_ < max_no_of_passengers_) {
        auto from_floor = static_cast<FloorNumber>(std::rand() % number_of_floors_);
        auto to_floor = static_cast<FloorNumber>(std::rand() % number_of_floors_);

        if (from_floor != to_floor) {
            Passenger *p = Passenger::create(from_floor, to_floor, time);
            no_of_passengers_ += 1;
            count_ += 1;
            return p;
        }
    }

    count_ = 0;
    return 0;
}
