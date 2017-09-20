//
// Elevator.cpp
//
#include "Elevator.h"
#include <assert.h>

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
        velocity_(velocity),
        floor_height_(floor_height),

        current_floor_(min_floor),
        target_floor_(min_floor),
        next_floor_(min_floor),

        height_(min_floor * floor_height),
        state_(State::IDLE),
        direction_(Direction::NONE) {
}

FloorNumber Elevator::current_floor() const {
    return current_floor_;
}

FloorNumber Elevator::target_floor() const {
    return target_floor_;
}

bool Elevator::is_idle() const {
    return state_ == State::IDLE;
}

bool Elevator::standing_on_floor(FloorNumber i) const {
    return is_idle() && current_floor_ == i;
}

void Elevator::clear_floor_button(FloorNumber number) {
    buttons_.erase(number);
}

void Elevator::press_floor_button(FloorNumber number) {
    buttons_.insert(number);
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
    assert(floor_number >= min_floor_ && floor_number < max_floor_);
    next_floor_ = floor_number;
}

/**
 * Move the elevator.
 *
 * If the elevator is standing still on a floor, a move of
 * the elevator is started as defined by next_floor_
 *
 * @param duration in seconds
 */
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
            state_ = State::WAITING;
        }
    } else if (target_floor_ < current_floor_) {
        state_ = State::MOVING;
        direction_ = Direction::DOWN;
        height_ -= velocity_ * duration;
        current_floor_ = static_cast<FloorNumber>((height_ + (floor_height_ - 1)) / floor_height_);
        if (height_ <= (int) target_floor_ * floor_height_) {
            height_ = target_floor_ * floor_height_;
            current_floor_ = target_floor_;
            state_ = State::WAITING;
        }
    } else {
        direction_ = Direction::NONE;
        state_ = State::IDLE;
    }
}

std::ostream &operator<<(std::ostream &os, Elevator &elevator) {
    os << std::string("elevator: ") << elevator.current_floor() << ": ";
    for (auto passenger : elevator.passengers()) {
        os << *passenger << " ";
    }
    return os;
}

// End of file
