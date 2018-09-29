//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

static const int VELOCITY = 5;
static const int FLOOR_HEIGHT = 4;

#include "Direction.h"
#include "Passenger.h"
#include "Car.h"
#include <set>
#include <QtCore>

class Elevator : public QObject
{
Q_OBJECT

public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    Elevator(FloorNumber *floor_array, size_t len, int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    Car &car()
    { return car_; }

    std::set<FloorNumber> &buttons()
    { return buttons_; }

    PassengerList &passengers()
    { return passengers_; }

    const std::set<FloorNumber> &floorNumbers() const;

    bool can_embark(std::shared_ptr<Passenger> passenger);

    bool can_disembark(std::shared_ptr<Passenger> passenger);

    // Button methods
    void clear_floor_button(FloorNumber);

    void press_floor_button(FloorNumber);

private:
    Car car_;
    std::set<FloorNumber> floors_;
    std::set<FloorNumber> buttons_;
    PassengerList passengers_;

};

std::ostream &operator<<(std::ostream &os, Elevator &elevator);

#endif //CHISS_ELEVATOR_H
