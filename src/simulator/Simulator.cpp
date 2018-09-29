//
// Simulator.cpp.
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
    for (auto p : (*traffic_generator_)(time))
    {
        inject_passenger(p);
        passengers_.push_back(p);
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

void Simulator::inject_passenger(std::shared_ptr<Passenger> passenger)
{
    for (Floor *floor : building_->floors())
    {
        if (floor->number() == passenger->begin_floor())
        {
            floor->passengers().push_back(passenger);
            floor->press_buttons(passenger->end_floor());
        }
    }
}

void Simulator::move_passengers(Time time)
{
    for (auto floor : building_->floors())
    {
        for (auto elevator : building_->elevators())
        {
            if (elevator->car().is_idle_on_floor(floor->number()))
            {
                floor->clear_buttons();
                elevator->clear_floor_button(floor->number());

                disembark(elevator, time);
                embark(floor, elevator, time);
            }
        }
    }
}

void Simulator::disembark(Elevator *elevator, Time time)
{
    PassengerList new_list;
    for (auto passenger : elevator->passengers())
    {
        if (elevator->can_disembark(passenger))
        {
            passenger->set_on_destination(time);
        }
        else
        {
            new_list.push_back(passenger);
        }
    }

    elevator->passengers().clear();
    std::copy(new_list.begin(), new_list.end(), std::back_inserter(elevator->passengers()));
}

void Simulator::embark(Floor *floor, Elevator *elevator, Time time)
{
    PassengerList new_list;
    for (const auto passenger : floor->passengers())
    {
        if (elevator->can_embark(passenger))
        {
            passenger->set_start_traveling(time);
            elevator->passengers().push_back(passenger);
            elevator->press_floor_button(passenger->end_floor());
        }
        else
        {
            new_list.push_back(passenger);
        }
    }

    floor->passengers().clear();
    std::copy(new_list.begin(), new_list.end(), std::back_inserter(floor->passengers()));
}

void Simulator::move_elevators(Duration dt)
{
    for (auto *elevator : building_->elevators())
    {
        elevator->car().move(dt);
    }
}

std::ostream &operator<<(std::ostream &os, Simulator &p)
{
    os << p.building();
    return os;
}

