//
// Created by ulf on 8/31/19.
//

#include "Stop.h"

/**
 * Elevator stop.
 *
 * A car traveling path can be seen as a circle there south
 * is minimum elevator floor and north is the maximum floor.
 *
 * index_ holds the position in that circle. Values between
 * minimum and maximum represent floors when the car is
 * going up and values between max and 2*max is then the
 * car is going down.
 *
 * @param floor_number
 * @param direction
 * @param car
 */
Stop::Stop(FloorNumber floor_number, Direction direction, Car *car) :
        floor_number_(floor_number),
        car_(car),
        index_(0)
{
    int mod = car->elevator()->mod();

    if (direction == Direction::UP)
    {
        index_ = (floor_number_ - car->current_floor()) % mod;
        if (index_ < 0) index_ += mod;
    }
    if (direction == Direction::DOWN)
    {
        index_ = -(floor_number_ - car->current_floor()) % mod;
        if (index_ < 0) index_ += mod;
    }
}

bool Stop::operator<(const Stop &b) const
{
    return index_ < b.index_;
}

bool Stop::operator==(const Stop &b) const
{
    return index_ == b.index_;
}

std::ostream &operator<<(std::ostream &os, Stop &)
{
#if 0
    if (s.travel_direction_ == Direction::UP)
        os << std::string(" ") << s.floor << "u";
    if (s.travel_direction_ == Direction::DOWN)
        os << std::string(" ") << s.floor << "d";
    if (s.travel_direction_ == Direction::NONE)
        os << std::string(" ") << s.floor << "-";
#endif
    return os;
}

// End of file