//
// ConstantTraffic.cpp.
//
#include "ConstantTraffic.h"

/**
 * Passenger generator functor.
 *
 * Generate new passengers at a constant rate. The passengers
 * are evenly distributed on all floors.
 *
 * @param number_of_floors
 * @param total_no_of_passengers
 * @param rate  passengers/step
 */
ConstantTraffic::ConstantTraffic(size_t number_of_floors,
                                 size_t total_no_of_passengers,
                                 double rate) :
        number_of_floors_(number_of_floors),
        max_no_of_passengers_(total_no_of_passengers),
        rate_(rate),
        no_of_passengers_(0),
        count_(0) {
}

/**
 * Passenger generator function.
 *
 * @param time
 * @return pointer to a new passenger or nullptr
 */
std::shared_ptr<Passenger> ConstantTraffic::operator()(Time time) {
    while (count_ < rate_ &&
           no_of_passengers_ < max_no_of_passengers_) {
        auto from_floor = static_cast<FloorNumber>(std::rand() % number_of_floors_);
        auto to_floor = static_cast<FloorNumber>(std::rand() % number_of_floors_);

        if (from_floor != to_floor) {
            std::shared_ptr<Passenger> p = std::make_shared<Passenger>(Passenger(from_floor, to_floor, time));
            no_of_passengers_ += 1;
            count_ += 1;
            return p;
        }
    }

    count_ = 0;
    return nullptr;
}

bool ConstantTraffic::done() const {
    return no_of_passengers_ >= max_no_of_passengers_;
}

// End of file