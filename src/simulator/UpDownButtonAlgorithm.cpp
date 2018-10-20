//
// UpDownButtonAlgorithm.cpp.
//

#include "UpDownButtonAlgorithm.h"
#include "Building.h"
#include <algorithm>
#include <iostream>

/**
 * Algorithm for two call buttons (up/down) on each floor.
 *
 * @param building
 */
void UpDownButtonAlgorithm::operator()(Building *building)
{
    for (Elevator *elevator : building->elevators())
    {
        std::vector<Stop> stops;

        for (FloorNumber x : elevator->destination_buttons())
        {
            stops.push_back(Stop(x));
        }

        for (const Floor *floor : building->floors())
        {
            if (floor->down_button())
            {
                stops.push_back(Stop(floor->number(), Direction::DOWN));
            }
            if (floor->up_button())
            {
                stops.push_back(Stop(floor->number(), Direction::UP));
            }
        }

        if (!stops.empty())
        {
            Comp comp(elevator->current_floor(), elevator->direction());
            std::sort(stops.begin(), stops.end(), comp);
            for (auto stop : stops)
            {
                if (stop.floor != elevator->current_floor())
                {
                    elevator->set_next_floor(stop.floor);
                    break;
                }
            }
        }
    }
}

/**
 * The compare function.
 *
 * @param a
 * @param b
 * @return true if stop a is better than stop b given a elevator position and direction
 */
bool UpDownButtonAlgorithm::Comp::operator()(const Stop &a, const Stop &b)
{
    int a_delta = a.floor - current_;
    int b_delta = b.floor - current_;
    Direction approach_dir_a = (a_delta < 0) ? Direction::DOWN : Direction::UP;
    Direction approach_dir_b = (b_delta < 0) ? Direction::DOWN : Direction::UP;

    // Prefer a stop in the elevator direction.
    if (approach_dir_a == direction_ && approach_dir_b != direction_)
    {
        return true;
    }
    if (approach_dir_a != direction_ && approach_dir_b == direction_)
    {
        return false;
    }

    // Prefer stop in travel direction
    if (a.direction == approach_dir_a && b.direction != approach_dir_b)
    {
        return true;
    }
    if (a.direction != approach_dir_a && b.direction == approach_dir_b)
    {
        return false;
    }

//    //
//    if (a.direction == Direction::DOWN && b.direction == Direction::DOWN) {
//        return a.floor > b.floor;
//    }
//    if (a.direction == Direction::UP && b.direction == Direction::UP) {
//        return a.floor < b.floor;
//    }
//
//    assert(false);

    // Shortest distance
    return std::abs(a_delta) < std::abs(b_delta);
}

std::ostream &operator<<(std::ostream &os, UpDownButtonAlgorithm::Stop &s)
{
    if (s.direction == Direction::UP)
        os << std::string(" ") << s.floor << "u";
    if (s.direction == Direction::DOWN)
        os << std::string(" ") << s.floor << "d";
    if (s.direction == Direction::NONE)
        os << std::string(" ") << s.floor << "-";
    return os;
}

// End of file
