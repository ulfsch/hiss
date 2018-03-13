//
// Car.h
//

#ifndef CHISS_CAR_H
#define CHISS_CAR_H


#include "common.h"
#include "Direction.h"

class Car {
public:
    Car(FloorNumber min_floor, int velocity, int floor_height);

    // Access methods
    FloorNumber current_floor() const;

    bool is_idle() const;
    bool is_idle_on_floor(FloorNumber i) const;

    Direction direction() const { return direction_; }

    // Elevator movement methods
    void set_next_floor(FloorNumber floor_number);
    void move(Duration dt);

    // Testing only
    void set_position(FloorNumber number, Direction direction);
    FloorNumber next_floor() const;

private:
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

};


#endif //CHISS_CAR_H
