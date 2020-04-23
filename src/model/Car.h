//
// Car.h
//

#ifndef CHISS_CAR_H
#define CHISS_CAR_H

#include "common.h"
#include "Elevator.h"

static const int VELOCITY = 2;
static const int FLOOR_HEIGHT = 4;


class Car
{
public:
    explicit Car(Elevator *elevator, int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    // Access methods
    Elevator *elevator() const;
    FloorNumber current_floor() const;

    double normalized_height() const;
    bool is_idle() const;
    bool is_idle_on_floor(FloorNumber i) const;

    // Elevator movement methods
    void set_next_floor(FloorNumber floor_number);
    void tick(MilliSeconds time);

    // Testing only
    FloorNumber next_floor() const;

private:
    Elevator *elevator_;
    const double velocity_;
    const double floor_height_;

    double height_;
    double target_height_;
    double start_height_;
    MilliSeconds start_time_;

    FloorNumber current_floor_;
    FloorNumber next_floor_;

    enum class State
    {
        IDLE, WAITING, MOVING_UP, MOVING_DOWN
    } state_;

};

typedef std::list<Car *> CarList;

#endif //CHISS_CAR_H
