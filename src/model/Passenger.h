//
// Passenger.h
//
#ifndef CHISS_PASSENGER_H
#define CHISS_PASSENGER_H

#include "common.h"
#include <list>
#include <ostream>
#include <memory>

class Passenger;

typedef std::list<std::shared_ptr<Passenger> > PassengerList;


class Passenger
{
public:
    Passenger(FloorNumber begin_floor, FloorNumber end_floor, Time time);

    Id id() const;
    FloorNumber begin_floor() const;
    FloorNumber end_floor() const;
    bool on_destination() const;

    Duration waiting_time() const;
    Duration traveling_time() const;

    void set_start_traveling(Time time);
    void set_on_destination(Time time);

private:
    static Id last_id_;
    Id id_;

    FloorNumber begin_floor_;
    FloorNumber end_floor_;

    Time begin_time_;
    Time pick_up_time_;
    Time end_time_;

};

std::ostream &operator<<(std::ostream &os, Passenger &p);

#endif //CHISS_PASSENGER_H