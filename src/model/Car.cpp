//
// Car.cpp
//

#include <cassert>
#include "Car.h"

/**
 *
 * @param elevator
 * @param velocity
 * @param floor_height
 */
Car::Car(Elevator *elevator, int velocity, int floor_height) :
        elevator_(elevator),
        velocity_(velocity),
        floor_height_(floor_height),

        current_floor_(elevator->min_floor()),
        target_floor_(elevator->min_floor()),
        next_floor_(elevator->min_floor()),

        height_(elevator->min_floor() * floor_height),
        state_(State::IDLE),
        direction_(Direction::UP)
{
}

Elevator *Car::elevator() const
{
    return elevator_;
}

FloorNumber Car::current_floor() const
{
    return current_floor_;
}

FloorNumber Car::next_floor() const
{
    return next_floor_;
}

bool Car::is_idle() const
{
    return state_ == State::IDLE;
}

bool Car::is_idle_on_floor(FloorNumber i) const
{
    return is_idle() && current_floor_ == i;
}

/**
 * Order the elevator to go to a floor.
 *
 * The order is delayed until the elevator has stopped on a floor.
 * Orders are not stacked. New values overwrites any old value.
 *
 * @param floor_number
 */
void Car::set_next_floor(FloorNumber floor_number)
{
    assert(elevator_->is_valid_floor(floor_number));
    next_floor_ = floor_number;
}

/**
 * Move the elevator car.
 *
 * If the elevator car is standing idle on a floor, a move of
 * the elevator is started as defined by next_floor_
 *
 * @param duration in seconds
 */
void Car::tick(Duration duration)
{
    if (is_idle())
    {
        target_floor_ = next_floor_;
    }

    if (target_floor_ > current_floor_)
    {
        state_ = State::MOVING;
        direction_ = Direction::UP;
        height_ += velocity_ * duration;
        current_floor_ = static_cast<FloorNumber>(height_ / floor_height_);
        if (height_ >= (int) target_floor_ * floor_height_)
        {
            height_ = target_floor_ * floor_height_;
            current_floor_ = target_floor_;
            state_ = State::WAITING;
        }
    }
    else if (target_floor_ < current_floor_)
    {
        state_ = State::MOVING;
        direction_ = Direction::DOWN;
        height_ -= velocity_ * duration;
        current_floor_ = static_cast<FloorNumber>((height_ + (floor_height_ - 1)) / floor_height_);
        if (height_ <= (int) target_floor_ * floor_height_)
        {
            height_ = target_floor_ * floor_height_;
            current_floor_ = target_floor_;
            state_ = State::WAITING;
        }
    }
    else
    {
        // direction_ = Direction::NONE;
        state_ = State::IDLE;
    }
}

void Car::set_position(FloorNumber number, Direction direction)
{
    current_floor_ = number;
    direction_ = direction;
}
