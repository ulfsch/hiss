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

void Simulator::tick(Time time, Duration dt)
{
    while (Passenger *p = (*traffic_generator_)(building_, time))
    {
        inject_passenger(p);
    }
    move_passengers(time);
    (*algorithm_)(building_);
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
    passenger->begin_floor()->press_buttons(passenger->end_floor()->number());
    passengers_.push_back(passenger);
}

void Simulator::move_passengers(Time time)
{
    // Disembark
    for (Passenger *p : passengers_)
    {
        if (p->elevator() && p->elevator()->is_idle_on(p->end_floor()->number()))
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
                if (elevator->is_idle_on(p->begin_floor()->number()))
                {
                    elevator->press_destination_button(p->end_floor()->number());
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
