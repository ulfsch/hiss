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

        height_(elevator->min_floor() * floor_height),
        target_height_(height_),
        start_height_(height_),
        start_time_(0),
        current_floor_(elevator->min_floor()),
        next_floor_(elevator->min_floor()),
        state_(State::IDLE),
        current_direction_(Direction::UP)
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

Direction Car::current_direction() const
{
    return current_direction_;
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
 * @param time in seconds
 */
void Car::tick(MilliSeconds time)
{
    MilliSeconds duration = time - start_time_;

    switch (state_)
    {
        case State::IDLE:
            if (next_floor_ != current_floor_)
            {
                target_height_ = next_floor_ * floor_height_;
                start_height_ = current_floor_ * floor_height_;
                start_time_ = time;
                state_ = (height_ < target_height_) ? State::MOVING_UP : State::MOVING_DOWN;
            }
            emit car_moved();
            break;

        case State::MOVING_UP:
            current_direction_ = Direction::UP;
            height_ = start_height_ + velocity_ * duration / 1000;
            if (height_ >= target_height_)
            {
                height_ = target_height_;
                current_floor_ = std::round(target_height_ / floor_height_);
                start_time_ = time;
                state_ = State::WAITING;
            }
            emit car_moved();
            break;

        case State::MOVING_DOWN:
            current_direction_ = Direction::DOWN;
            height_ = start_height_ - velocity_ * duration / 1000;
            if (height_ <= target_height_)
            {
                height_ = target_height_;
                current_floor_ = std::round(target_height_ / floor_height_);
                start_time_ = time;
                state_ = State::WAITING;
            }
            emit car_moved();
            break;

        case (State::WAITING):
            if (duration >= 1000)
            {
                start_time_ = time;
                state_ = State::IDLE;
            }
            break;
    }
}

double Car::normalized_height() const
{
    return height_ / floor_height_;
}

void Car::set_current_floor(FloorNumber floor_number, Direction direction)
{
    current_floor_ = floor_number;
    current_direction_ = direction;
}

int Car::get_index() const
{
    return (current_direction_ == Direction::DOWN) ? -current_floor_ : current_floor_;
}
