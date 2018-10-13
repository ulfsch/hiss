//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

#include "Car.h"
#include "Direction.h"
#include <set>
#include <QtCore>

typedef std::set<FloorNumber> NumberSet;

static const int VELOCITY = 5;
static const int FLOOR_HEIGHT = 4;


class Elevator : public QObject
{
Q_OBJECT

public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, QObject *parent = nullptr,
             int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    Elevator(FloorNumber *floor_array, size_t len, QObject *parent = nullptr,
             int velocity = VELOCITY, int floor_height = FLOOR_HEIGHT);

    FloorNumber max_floor() const { return max_floor_; }
    FloorNumber current_floor() const { return car_.current_floor(); }
    const NumberSet &floorNumbers() const { return floors_; }
    const NumberSet &destination_buttons() const { return destination_buttons_; }

    void move(Duration dt);
    bool is_idle_on(FloorNumber) const;

    // Button methods
    void clear_destination_button();
    void press_destination_button(FloorNumber);

    Car &car() { return car_; }

signals:
    void changed();

private:
    FloorNumber min_floor_;
    FloorNumber max_floor_;
    Car car_;
    NumberSet floors_;
    NumberSet destination_buttons_;

};

std::ostream &operator<<(std::ostream &os, const Elevator &elevator);

#endif //CHISS_ELEVATOR_H
