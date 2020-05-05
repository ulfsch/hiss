//
// Created by ulf on 8/20/19.
//

#include "StandardAlgorithm.h"

void StandardAlgorithm::operator()(CarList &cars, ControlPanel &controlPanel, StopVector &result)
{
    std::set<Stop> stops;

    // Create a stop list for all cars
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

// End of file
