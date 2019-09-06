//
// Created by ulf on 8/31/19.
//

#include "Stop.h"

bool Stop::operator<(const Stop &b) const
{
    // Prefer a stop in the elevator direction.
    if (in_elevator_direction_ && !b.in_elevator_direction_)
    {
        return true;
    }
    if (!in_elevator_direction_ && b.in_elevator_direction_)
    {
        return false;
    }

    // Prefer stop in travel direction
    if (in_travel_direction_ && !b.in_travel_direction_)
    {
        return true;
    }
    if (!in_travel_direction_ && b.in_travel_direction_)
    {
        return false;
    }

    // Shortest distance
    if (distance_ < b.distance_)
    {
        return true;
    }
    return this < &b;
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