//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

#include "Passenger.h"
#include <set>

class Elevator {
public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, int velocity=5, int floor_height=4);

    PassengerList &passengers() { return passengers_; }

    std::set<FloorNumber> &buttons() { return buttons_; }

    bool standing_on_floor(FloorNumber i) const;
    bool is_idle() const;

    Direction direction() const { return direction_; }

    FloorNumber current_floor() const;
    FloorNumber target_floor() const;

    void go_to(FloorNumber floor_number);
    void move(Duration dt);
    void clear_buttons();
    void press_buttons(Passenger *passenger);

private:
    PassengerList passengers_;
    std::set<FloorNumber> buttons_;

private:
    FloorNumber min_floor_;
    FloorNumber max_floor_;
    FloorNumber current_floor_;
    FloorNumber target_floor_;
    FloorNumber next_floor_;

    const int velocity_;
    const int floor_height_;
    int height_;

    enum class State {
        IDLE, WAITING, MOVING
    } state_;
    Direction direction_;

};

std::ostream& operator<<(std::ostream& os, Elevator& elevator);

#endif //CHISS_ELEVATOR_H
