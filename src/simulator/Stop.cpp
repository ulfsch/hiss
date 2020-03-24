//
// Created by ulf on 8/31/19.
//

#include "Stop.h"

Stop::Stop(FloorNumber floor_number, Direction direction, Car *car) :
        floor_number_(floor_number),
        car_(car),
        index_(0)
{
    int mod = car->elevator()->mod();

    if (direction == Direction::UP)
    {
        index_ = (floor_number_ - car->current_floor()) % mod;
    }
    if (direction == Direction::DOWN)
    {
        index_ = -(floor_number_ - car->current_floor()) % mod;
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