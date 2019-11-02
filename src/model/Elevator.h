//
// Elevator.h.
//
#ifndef CHISS_ELEVATOR_H
#define CHISS_ELEVATOR_H

#include "common.h"
#include <QtCore>



class Elevator : public QObject
{
Q_OBJECT

public:
    Elevator(FloorNumber min_floor, FloorNumber max_floor, QObject *parent = nullptr);
    Elevator(FloorNumber *floor_array, size_t len, QObject *parent = nullptr);

    // Get methods
    FloorNumber max_floor() const { return max_floor_; }

    FloorNumber min_floor() const
    { return min_floor_; }
    const NumberSet &floorNumbers() const { return floors_; }

signals:
    void changed();

private:
    FloorNumber min_floor_;
    FloorNumber max_floor_;
    NumberSet floors_;

};

#endif //CHISS_ELEVATOR_H
