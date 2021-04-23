//
// TrivialAlgorithm.cpp
//

#include "TrivialAlgorithm.h"

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

TrivialAlgorithm::TrivialAlgorithm()
{

}

void TrivialAlgorithm::operator()(CarList &cars, ControlPanel& controlPanel, std::vector<Stop> &result)
{
    std::vector<Stop> stops;

    // First check elevator buttons
    for (std::pair<Car *const, NumberSet> &panel : controlPanel.car_target_buttons)
    {
        for (int floor_number : panel.second)
        {
            stops.push_back(Stop(floor_number, Direction::UP, panel.first));
            stops.push_back(Stop(floor_number, Direction::DOWN
                    , panel.first));
        }
    }

    // Check floor call buttons.
    for (Car *car : cars)
    {
//        for (FloorNumber floor_number: controlPanel.floor_call_buttons)
//        {
//            stops.push_back(Stop(car, floor_number, Direction::NONE));
//        }

        for (FloorNumber floor_number: controlPanel.floor_up_buttons)
        {
            stops.push_back(Stop(floor_number, Direction::UP, car));
        }
        for (FloorNumber floor_number: controlPanel.floor_down_buttons)
        {
            stops.push_back(Stop(floor_number, Direction::DOWN, car));
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
