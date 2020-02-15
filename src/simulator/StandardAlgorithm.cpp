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

        if (stop_.floor_number != b.floor_number)
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
void StandardAlgorithm::operator()(Simulator *simulator, ControlPanel &controlPanel, std::vector<Stop> &result)
{
    std::vector<Stop> stops;

    for (std::pair<Car *const, NumberSet> &panel : controlPanel.car_target_buttons)
    {
        for (int floor_number : panel.second)
        {
            stops.push_back(Stop(panel.first, floor_number, Direction::NONE));
        }

    }

    for (Car *car : simulator->cars())
    {
        for (FloorNumber floor_number: controlPanel.floor_call_buttons)
        {
            stops.push_back(Stop(car, floor_number, Direction::NONE));
        }
        for (FloorNumber floor_number: controlPanel.floor_up_buttons)
        {
            stops.push_back(Stop(car, floor_number, Direction::UP));
        }
        for (FloorNumber floor_number: controlPanel.floor_down_buttons)
        {
            stops.push_back(Stop(car, floor_number, Direction::DOWN));
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
