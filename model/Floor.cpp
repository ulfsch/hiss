//
// Floor.cpp
//
#include <ostream>
#include "Floor.h"

Floor::Floor(FloorNumber floor_number) :
        number_(floor_number),
        call_button_(false),
        up_button_(false),
        down_button_(false) {
}

void Floor::press_buttons(std::shared_ptr<Passenger> passenger) {
    call_button_ = true;

    if (passenger->end_floor() > number_) {
        up_button_ = true;
    }
    if (passenger->end_floor() < number_) {
        down_button_ = true;
    }
}

void Floor::clear_buttons() {
    call_button_ = false;
    up_button_ = false;
    down_button_ = false;
}

std::ostream &operator<<(std::ostream &os, Floor &floor) {
    os << std::string("floor ") << floor.number() << ": ";
    for (auto passenger : floor.passengers()) {
        os << *passenger << " ";
    }
    return os;
}

// End of file
