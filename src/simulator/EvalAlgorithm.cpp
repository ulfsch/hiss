//
// Created by ulf on 8/20/19.
//

#include <Building.h>
#include <Elevator.h>
#include "EvalAlgorithm.h"
#include "Simulator.h"

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


void EvalAlgorithm::operator()(Simulator *simulator, ControlPanel &controlPanel, std::vector<Stop> &result)
{
    std::vector<Stop> stops;

    for (std::pair<Car *const, NumberSet> &panel : controlPanel.car_target_buttons)
    {
        for (int floor_number : panel.second)
        {
            result.push_back(Stop(panel.first, floor_number, Direction::NONE));
        }
    }

    for (FloorNumber floor_number: controlPanel.floor_up_buttons)
    {
        stops.push_back(Stop(nullptr, floor_number, Direction::UP));
    }
    for (FloorNumber floor_number: controlPanel.floor_down_buttons)
    {
        stops.push_back(Stop(nullptr, floor_number, Direction::DOWN));
    }

    std::sort(stops.begin(), stops.end());

    uint32_t nbr_cars = simulator->cars().size();
    uint32_t nbr_stops = stops.size();
    uint32_t sector_size = nbr_stops / nbr_cars + 0;

    uint32_t i = 0;
    auto j = simulator->cars().begin();
    while (j != simulator->cars().end() && i < nbr_stops)
    {
        Car *car = *j;

        if (i < nbr_stops)
        {
            Stop stop = stops[i++];
            stop.set_car(car);
            result.push_back(stop);
        }

        if (sector_size == 0 || i % sector_size == 0)
        {
            ++j;
        }
    }

   //std::sort(result.begin(), result.end());
}
