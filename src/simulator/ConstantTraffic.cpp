//
// ConstantTraffic.cpp.
//
#include "ConstantTraffic.h"
#include "Building.h"
/**
 * Constructor.
 *
 * @param rate  passengers/step
 */
ConstantTraffic::ConstantTraffic(size_t number_of_floors,
                                 size_t total_no_of_passengers,
                                 double rate) :
        number_of_floors_(number_of_floors),
        max_no_of_passengers_(total_no_of_passengers),
        rate_(rate),
        no_of_passengers_(0),
        count_(0)
{
}

/**
 * Passenger generator function.
 *
 * Generate new passengers at a constant rate. The passengers
 * are evenly distributed on all floors.
 *
 * @param time the begin_time for the generated passengers
 * @return list of new passengers generated in one step
 */
Passenger *ConstantTraffic::operator()(Building *building, Time time)
{
    if (count_ >= 1 && no_of_passengers_ < max_no_of_passengers_)
    {
        auto from_floor = static_cast<FloorNumber>(std::rand() % number_of_floors_);
        auto to_floor = static_cast<FloorNumber>(std::rand() % number_of_floors_);

        if (from_floor != to_floor)
        {
            Passenger *p = new Passenger(from_floor, to_floor, time);
            no_of_passengers_ += 1;
            count_ -= 1;
            return p;
        }
    }
    count_ += rate_;
    return nullptr;
}

/**
 *
 * @return true when all passengers are generated
 */
bool ConstantTraffic::done() const
{
    return no_of_passengers_ >= max_no_of_passengers_;
}

// End of file