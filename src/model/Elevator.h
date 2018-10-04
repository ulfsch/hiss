//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

static const int VELOCITY = 5;
static const int FLOOR_HEIGHT = 4;

#include "Car.h"
#include "Direction.h"
#include "Passenger.h"
#include <set>
#include <QtCore>

class Elevator : public QObject
{
Q_OBJECT

public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, QObject *parent,
             int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    Elevator(FloorNumber *floor_array, size_t len, QObject *parent,
             int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    Car &car()
    { return car_; }

    PassengerList &passengers()
    { return passengers_; }

    std::set<FloorNumber> &buttons()
    { return buttons_; }
    const std::set<FloorNumber> &floorNumbers() const;

    FloorNumber max_floor() const
    { return max_floor_; }

    void move(Duration dt);

    bool can_embark(std::shared_ptr<Passenger> passenger);
    bool can_disembark(std::shared_ptr<Passenger> passenger);

    // Button methods
    void clear_floor_button(FloorNumber);
    void press_floor_button(FloorNumber);

signals:

    void changed();

private:
    FloorNumber min_floor_;
    FloorNumber max_floor_;
    Car car_;
    std::set<FloorNumber> floors_;
    std::set<FloorNumber> buttons_;
    PassengerList passengers_;

};

std::ostream &operator<<(std::ostream &os, Elevator &elevator);

#endif //CHISS_ELEVATOR_H
