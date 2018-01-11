//
// Elevator.cpp
//
#include "Elevator.h"

/**
 * Constructor.
 * 
 * @param min_floor lowest floor number. Bottom floor is 0
 * @param max_floor highest floor number + 1
 * @param velocity  elevator speed in m/s
 * @param floor_height in meter
 */
Elevator::Elevator(FloorNumber min_floor, FloorNumber max_floor, int velocity, int floor_height) :
        car_(min_floor, velocity, floor_height) {
    for (FloorNumber i = min_floor; i < max_floor; i++) {
        floors_.insert(i);
    }
}

/**
 * Constructor.
 *
 * @param floor_array array of floor numbers
 * @param len length of array
 * @param velocity  elevator speed in m/s
 * @param floor_height in meter
 */
Elevator::Elevator(FloorNumber floor_array[], size_t len, int velocity, int floor_height) :
        car_(floor_array[0], velocity, floor_height),
        floors_(floor_array, floor_array + len) {
}

void Elevator::clear_floor_button(FloorNumber number) {
    buttons_.erase(number);
}

void Elevator::press_floor_button(FloorNumber number) {
    buttons_.insert(number);
}

bool Elevator::can_embark(std::shared_ptr<Passenger> passenger) {
    return (passenger->begin_floor() == car().current_floor());
}

bool Elevator::can_disembark(std::shared_ptr<Passenger> passenger) {
    return (passenger->end_floor() == car().current_floor());
}


std::ostream &operator<<(std::ostream &os, Elevator &elevator) {
    os << std::string("elevator: ") << elevator.car().current_floor() << ": ";
    for (auto passenger : elevator.passengers()) {
        os << *passenger << " ";
    }
    return os;
}

// End of file
