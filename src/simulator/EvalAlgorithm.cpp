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
        if (stop_.car_ == b.car_)
        {
            return true;
        }

        if (stop_.floor_number_ != b.floor_number_)
        {
            return false;
        }

        return true;
    }

    Stop stop_;
};

void EvalAlgorithm::operator()(CarList &cars, ControlPanel &controlPanel, std::vector<Stop> &result)
{
    std::set<Stop> stops;

    for (Car *car : cars)
    {
        for (FloorNumber floor_number : controlPanel.car_target_buttons[car])
        {
            stops.insert(Stop(floor_number, Direction::UP, car));
            stops.insert(Stop(floor_number, Direction::DOWN, car));
        }
        for (FloorNumber floor_number: controlPanel.floor_up_buttons)
        {
            stops.insert(Stop(floor_number, Direction::UP, car));
        }
        for (FloorNumber floor_number: controlPanel.floor_down_buttons)
        {
            stops.insert(Stop(floor_number, Direction::DOWN, car));
        }
    }

    for (Car *car : cars)
    {
        if (car->is_idle())
        {
            for (Stop stop : stops)
            {
                if (car == stop.car())
                {
                    result.push_back(stop);
                    break;
                }
            }
        }
    }
}

