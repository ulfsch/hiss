//
// Simulator.cpp
//
#include "Simulator.h"
#include <algorithm>
#include <iostream>

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
}

void Simulator::tick(Time time, Duration dt)
{
    while (Passenger *p = (*traffic_generator_)(building_, time))
    {
        inject_passenger(p);
    }
    move_passengers(time);
    std::vector<Stop> stops;
    (*algorithm_)(building_, stops);
    for (const auto &stop : stops)
    {
        // if (stop.floor != elevator->current_floor())
        stop.elevator->set_next_floor(stop.floor);
    }
    move_elevators(dt);
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

void Simulator::move_passengers(Time time)
{
    // Disembark
    for (Passenger *p : passengers_)
    {
        if (p->elevator() && p->elevator()->is_idle_on(p->end_floor()))
        {
            p->set_on_destination(time);
        }
    }

    // Embark
    for (Passenger *p : passengers_)
    {
        if (p->on_start_floor())
        {
            for (Elevator *elevator : building_->elevators())
            {
                if (elevator->is_idle_on(p->begin_floor()))
                {
                    elevator->press_destination_button(p->end_floor());
                    p->set_start_traveling(elevator, time);
                    break;
                }
            }
        }
    }
}

void Simulator::move_elevators(Duration dt)
{
    for (Elevator *elevator : building_->elevators())
    {
        elevator->move(dt);
        elevator->clear_destination_button();
        for (Floor *floor : building_->floors())
        {
            if (elevator->is_idle_on(floor->number()))
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
