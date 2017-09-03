//
// Simulator.cpp.
//
#include "Simulator.h"
#include <algorithm>
#include <iostream>

Simulator::Simulator(Traffic &traffic, Algorithm &algorithm, Building &building) :
        traffic_(traffic),
        algorithm_(algorithm),
        building_(building) {

}

void Simulator::step(Time time, Duration dt) {
    while (Passenger *passenger = traffic_(time)) {
        inject_passenger(passenger);
    }
    move_passengers(time);
    algorithm_(building_);
    move_elevators(dt);
}

bool Simulator::done() const {
    return traffic_.done() && Passenger::all_at_destination();
}

void Simulator::inject_passenger(Passenger *passenger) {
    for (Floor &floor : building_.floors()) {
        if (floor.number() == passenger->begin_floor()) {
            floor.passengers().push_back(passenger);
            floor.press_buttons(passenger);
        }
    }
}

void Simulator::move_passengers(Time time) {
    for (auto &floor : building_.floors()) {
        for (auto &elevator : building_.elevators()) {
            if (elevator.standing_on_floor(floor.number())) {
                floor.clear_buttons();
                elevator.clear_buttons();

                disembark(elevator, floor, time);
                embark(floor, elevator, time);
            }
        }
    }
}

void Simulator::disembark(Elevator &elevator, Floor &floor, Time time) {
    PassengerList new_list;
    for (auto *passenger : elevator.passengers()) {
        if (passenger->on_end_floor(floor.number())) {
            passenger->set_on_destination(time);
            floor.passengers().push_back(passenger);
//            floor.press_buttons(passenger);
        } else {
            new_list.push_back(passenger);
        }
    }

    elevator.passengers().clear();
    std::copy(new_list.begin(), new_list.end(), std::back_inserter(elevator.passengers()));
}

void Simulator::embark(Floor &floor, Elevator &elevator, Time time) {
    PassengerList new_list;
    for (auto *passenger : floor.passengers()) {
        if (passenger->on_begin_floor(floor.number())) {
            passenger->set_start_traveling(time);
            elevator.passengers().push_back(passenger);
            elevator.press_buttons(passenger);
        } else {
            new_list.push_back(passenger);
        }
    }

    floor.passengers().clear();
    std::copy(new_list.begin(), new_list.end(), std::back_inserter(floor.passengers()));
}

void Simulator::move_elevators(Duration dt) {
    for (auto &elevator : building_.elevators()) {
        elevator.move(dt);
    }
}


