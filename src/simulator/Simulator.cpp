//
// Simulator.cpp
//
#include "Simulator.h"
#include <algorithm>


Simulator::Simulator(Traffic *traffic, Algorithm *algorithm, Building *building) :
        traffic_generator_(traffic),
        algorithm_(algorithm),
        building_(building),
        last_time_(0)
{
    for (Elevator *elevator : building_->elevators())
    {
        Car* car = new Car(elevator);
        cars_.push_back(car);
        // control_panels_.car_target_buttons.insert(std::pair<Car*, NumberSet>(car, NumberSet()));
    }
}

Simulator::~Simulator()
{
    for (const auto &passenger : passengers_)
    {
        delete passenger;
    }
    passengers_.clear();

    for (const auto &car : cars_)
    {
        delete car;
    }
    cars_.clear();
}

void Simulator::tick(MilliSeconds time)
{
    // Move all cars
    for (Car *car : cars_)
    {
        car->tick(time);
    }

    if (time / SIMULATION_RATE != last_time_ / SIMULATION_RATE)
    {
        last_time_ = time;

        // Move passengers
        move_passengers(time);

        // Inject new passengers
        while (Passenger *passenger = (*traffic_generator_)(building_, time))
        {
            passengers_.push_back(passenger);
            control_panels_.press_floor_buttons(passenger);
        }

        // Execute algorithm
        std::vector<Stop> stops;
        (*algorithm_)(cars_, control_panels_, stops);

        // Control the cars
        for (const auto &stop : stops)
        {
            stop.car_->set_next_floor(stop.floor_number_);
            control_panels_.clear_floor_buttons(stop.floor_number_);
            control_panels_.clear_car_buttons(stop.car(), stop.floor_number_);
        }
    }

}

bool Simulator::done() const
{
    if (!traffic_generator_->done())
    {
        return false;
    }

    // Check if all passengers at destination
    for (auto p : passengers_)
    {
        if (!p->on_destination())
        {
            return false;
        }
    }

    return true;
}

void Simulator::move_passengers(MilliSeconds time)
{
    // Disembark
    for (Passenger *p : passengers_)
    {
        if (p->car() && p->car()->is_idle_on_floor(p->end_floor()))
        {
            p->set_on_destination(time);
        }
    }

    // Embark
    for (Passenger *p : passengers_)
    {
        if (p->on_start_floor())
        {
            for (Car *car : cars_)
            {
                if (car->is_idle_on_floor(p->begin_floor()))
                {
                    control_panels_.press_car_buttons(car, p);
                    p->set_start_traveling(car, time);
                    break;
                }
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, Simulator &p)
{
    os << p.building();
    return os;
}

// End of file
