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
        min_floor_(min_floor),
        max_floor_(max_floor),
        current_floor_(min_floor),
        target_floor_(min_floor),
        next_floor_(min_floor),
        velocity_(velocity),
        floor_height_(floor_height),
        height_(min_floor * floor_height),
        state_(State::IDLE),
        direction_(Direction::NONE) {
}

/**
 * Order the elevator to go to a floor. 
 * 
 * The order is delayed until the elevator has stopped on a floor.
 * Orders are not stacked. New values overwrites any old value.
 * 
 * @param floor_number 
 */
void Elevator::go_to(FloorNumber floor_number) {
    next_floor_ = floor_number;
}

bool Elevator::is_idle() const {
    return state_ == State::IDLE;
}

bool Elevator::standing_on_floor(FloorNumber i) const {
    return is_idle() && current_floor_ == i;
}

FloorNumber Elevator::current_floor() const {
    return current_floor_;
}

FloorNumber Elevator::target_floor() const {
    return target_floor_;
}

void Elevator::clear_buttons() {
    buttons_.erase(current_floor_);
}

void Elevator::press_buttons(Passenger *passenger) {
    buttons_.insert(passenger->end_floor());
}

void Elevator::move(Duration duration) {
    if (is_idle()) {
        target_floor_ = next_floor_;
    }

    if (target_floor_ > current_floor_) {
        state_ = State::MOVING;
        direction_ = Direction::UP;
        height_ += velocity_ * duration;
        current_floor_ = static_cast<FloorNumber>(height_ / floor_height_);
        if (height_ >= (int) target_floor_ * floor_height_) {
            height_ = target_floor_ * floor_height_;
            current_floor_ = target_floor_;
            state_ = State::IDLE;
        }
    } else if (target_floor_ < current_floor_) {
        state_ = State::MOVING;
        direction_ = Direction::DOWN;
        height_ -= velocity_ * duration;
        current_floor_ = static_cast<FloorNumber>((height_ + (floor_height_ - 1)) / floor_height_);
        if (height_ <= (int) target_floor_ * floor_height_) {
            height_ = target_floor_ * floor_height_;
            current_floor_ = target_floor_;
            state_ = State::IDLE;
        }
    } else {
        direction_ = Direction::NONE;
    }
}

std::ostream &operator<<(std::ostream &os, Elevator &elevator) {
    os << std::string("elevator: ") << elevator.current_floor() << ": ";
    for (Passenger *passenger : elevator.passengers()) {
        os << *passenger << " ";
    }
    return os;
}

// End of file
