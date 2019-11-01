//
// StandardAlgorithm.cpp.
//

#include "StandardAlgorithm.h"
#include "Building.h"
#include "Simulator.h"
#include "Stop.h"
#include <algorithm>

struct IsSame
{
    IsSame(const Stop &stop) : stop_(stop)
    {}

    bool operator()(const Stop &b)
    {
        if (stop_.car == b.car)
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
 * @param simulator
 */
void StandardAlgorithm::operator()(Simulator *simulator, std::vector<Stop> &result)
{
    std::vector<Stop> stops;

    for (Car *car : simulator->cars())
    {
        for (FloorNumber floor_number : car->destination_buttons())
        {
            stops.push_back(Stop(car, floor_number, Direction::NONE));
        }

        for (Floor *floor : simulator->building()->floors())
        {
            if (floor->down_button())
            {
                stops.push_back(Stop(car, floor->number(), Direction::DOWN));
            }
            if (floor->up_button())
            {
                stops.push_back(Stop(car, floor->number(), Direction::UP));
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
