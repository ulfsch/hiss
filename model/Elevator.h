//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

static const int VELOCITY = 5;
static const int FLOOR_HEIGHT = 4;

#include "Direction.h"
#include "Passenger.h"
#include <set>

class Elevator {
public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);
    Elevator(FloorNumber *floor_array, size_t len, int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    // Access methods
    FloorNumber target_floor() const;
    FloorNumber current_floor() const;
    FloorNumber next_floor() const;

    Direction direction() const { return direction_; }
    PassengerList &passengers() { return passengers_; }
    std::set<FloorNumber> &buttons() { return buttons_; }

    bool can_embark(std::shared_ptr<Passenger> passenger);
    bool can_disembark(std::shared_ptr<Passenger> passenger);

    // Elevator movement methods
    bool is_idle() const;
    bool standing_on_floor(FloorNumber i) const;
    void go_to(FloorNumber floor_number);
    void move(Duration dt);

    // Button methods
    void clear_floor_button(FloorNumber);
    void press_floor_button(FloorNumber);

    // Testing only
    void set_position(FloorNumber number, Direction direction);

private:
    std::set<FloorNumber> floors_;

    const int velocity_;
    const int floor_height_;

    FloorNumber current_floor_;
    FloorNumber target_floor_;
    FloorNumber next_floor_;
    int height_;

    enum class State {
        IDLE, WAITING, MOVING
    } state_;
    Direction direction_;

    PassengerList passengers_;
    std::set<FloorNumber> buttons_;

};

std::ostream &operator<<(std::ostream &os, Elevator &elevator);

#endif //CHISS_ELEVATOR_H
