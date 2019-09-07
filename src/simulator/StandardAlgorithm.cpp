//
// StandardAlgorithm.cpp.
//

#include "StandardAlgorithm.h"
#include "Building.h"
#include "Stop.h"
#include <algorithm>
#include <iostream>

struct IsSame
{
    IsSame(const Stop &stop) : stop_(stop)
    {}

    bool operator()(const Stop &b)
    {
        if (stop_.elevator == b.elevator)
        {
            return true;
        }

        if (stop_.floor != b.floor)
        {
            return false;
        }

        return (stop_.direction == b.direction);
    }

    Stop stop_;
};

/**
 * Algorithm for two call buttons (up/down) on each floor.
 *
 * @param building
 */
void StandardAlgorithm::operator()(Building *building, std::vector<Stop> &result)
{
    std::vector<Stop> stops;

    for (Elevator *elevator : building->elevators())
    {
        for (FloorNumber floor_number : elevator->destination_buttons())
        {
            stops.push_back(Stop(elevator, floor_number, Direction::NONE));
        }

        for (Floor *floor : building->floors())
        {
            if (floor->down_button())
            {
                stops.push_back(Stop(elevator, floor->number(), Direction::DOWN));
            }
            if (floor->up_button())
            {
                stops.push_back(Stop(elevator, floor->number(), Direction::UP));
            }
        }
    }

    std::sort(stops.begin(), stops.end());

    result.clear();
    for (auto stop : stops)
    {
        if (std::find_if(result.begin(), result.end(), IsSame(stop)) == result.end())
        {
            result.push_back(stop);
        }
    }
}

// End of file
