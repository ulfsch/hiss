//
// Simulator.cpp
//
#include "Simulator.h"
#include "Stop.h"
#include <algorithm>

Simulator::Simulator(Traffic *traffic, Algorithm *algorithm, Building *building) :
        traffic_generator_(traffic),
        algorithm_(algorithm),
        building_(building)
{
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

void Simulator::tick(Time time, Duration dt)
{
    while (Passenger *p = (*traffic_generator_)(building_, time))
    {
        inject_passenger(p);
    }
    std::vector<Stop> stops;
    (*algorithm_)(this, stops);
    for (const auto &stop : stops)
    {
        if (stop.floor != stop.car->current_floor())
        {
            stop.car->set_next_floor(stop.floor);
        }
    }
    move_cars(dt);
    move_passengers(time);
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

void Simulator::inject_passenger(Passenger *passenger)
{
    passengers_.push_back(passenger);
    building_->floor(passenger->begin_floor())->press_buttons(passenger->end_floor());
}

void Simulator::inject_cars()
{
    for (Elevator *elevator : building_->elevators())
    {
        Car *car = new Car(elevator);
        cars_.push_back(car);
    }
}

void Simulator::move_passengers(Time time)
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
                    car->press_destination_button(p->end_floor());
                    p->set_start_traveling(car, time);
                    break;
                }
            }
        }
    }
}

void Simulator::move_cars(Duration dt)
{
    for (Car *car : cars_)
    {
        car->move(dt);
        car->clear_destination_button();
        for (Floor *floor : building_->floors())
        {
            if (car->is_idle_on_floor(floor->number()))
            {
                floor->clear_buttons();
                break;
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
