//
// Passenger.h
//
#ifndef CHISS_PASSENGER_H
#define CHISS_PASSENGER_H

#include "common.h"
#include <ostream>
#include <list>

class Car;


class Passenger
{
public:
    Passenger(FloorNumber begin_floor, FloorNumber end_floor, MilliSeconds time = 0);

    Id id() const;
    FloorNumber begin_floor() const;
    FloorNumber end_floor() const;

    Car *car() const;

    bool on_start_floor() const;
    bool on_destination() const;
    MilliSeconds waiting_time() const;

    MilliSeconds traveling_time() const;

    void set_start_traveling(Car *car, MilliSeconds time);
    void set_on_destination(MilliSeconds time);
    int print() const;

private:
    static Id last_id_;
    Id id_;

    FloorNumber begin_floor_;
    FloorNumber end_floor_;
    Car *car_;

    MilliSeconds begin_time_;
    MilliSeconds pick_up_time_;
    MilliSeconds end_time_;

};

std::ostream &operator<<(std::ostream &os, Passenger &p);

typedef std::list<Passenger *> PassengerList;

#endif //CHISS_PASSENGER_H
