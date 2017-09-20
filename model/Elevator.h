//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

#include "Passenger.h"
#include <set>

class Elevator {
public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, int velocity = 5, int floor_height = 4);

    // Access methods
    FloorNumber target_floor() const;
    FloorNumber current_floor() const;

    Direction direction() const { return direction_; }
    PassengerList &passengers() { return passengers_; }
    std::set<FloorNumber> &buttons() { return buttons_; }

    // Elevator movement methods
    bool is_idle() const;
    bool standing_on_floor(FloorNumber i) const;
    void go_to(FloorNumber floor_number);
    void move(Duration dt);

    // Button methods
    void clear_floor_button(FloorNumber);
    void press_floor_button(FloorNumber);

private:
    const FloorNumber min_floor_;
    const FloorNumber max_floor_;
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
