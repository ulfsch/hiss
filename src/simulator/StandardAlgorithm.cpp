//
// Created by ulf on 8/20/19.
//

#include "StandardAlgorithm.h"

void StandardAlgorithm::operator()(CarList &cars, ControlPanel& control_panel, StopVector &result)
{
    std::set<Stop> stops;

    // Create a stop list for all cars
    for (Car *car : cars)
    {
        for (FloorNumber floor_number : control_panel.car_target_buttons[car])
        {
            stops.insert(Stop(floor_number, Direction::ANY, car));
        }
        for (FloorNumber floor_number: control_panel.floor_up_buttons)
        {
            stops.insert(Stop(floor_number, Direction::UP, car));
            //control_panel.clear_floor_buttons(floor_number);
        }
        for (FloorNumber floor_number: control_panel.floor_down_buttons)
        {
            stops.insert(Stop(floor_number, Direction::DOWN, car));
            // control_panel.clear_floor_buttons(floor_number);
        }
    }

#if 1
    std::vector<Car*> assigned;

    for (Stop stop : stops)
    {
        Car* car = stop.car();
        if (car->is_idle())
        {
            if (std::find(assigned.begin(), assigned.end(), car) == assigned.end())
            {
                result.push_back(stop);
                //control_panel.clear_floor_buttons(stop.floor_number_);
                //control_panel.clear_car_buttons(stop.car(), stop.floor_number_);

                assigned.push_back(car);
            }
        }
    }
#else
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
#endif
}

// End of file
