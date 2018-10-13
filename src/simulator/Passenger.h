//
// Passenger.h
//
#ifndef CHISS_PASSENGER_H
#define CHISS_PASSENGER_H

#include "common.h"
#include <ostream>
#include <list>

class Building;
class Floor;
class Elevator;


class Passenger
{
public:
    Passenger(Floor *begin_floor, Floor *end_floor, Time time);

    Id id() const;
    Floor *begin_floor() const;
    Floor *end_floor() const;
    Elevator *elevator() const;

    bool on_start_floor() const;
    bool on_destination() const;
    Duration waiting_time() const;

    Duration traveling_time() const;
    void set_start_traveling(Elevator *elevator, Time time);
    void set_on_destination(Time time);

private:
    static Id last_id_;
    Id id_;

    Floor *begin_floor_;
    Floor *end_floor_;
    Elevator* elevator_;

    Time begin_time_;
    Time pick_up_time_;
    Time end_time_;

};

std::ostream &operator<<(std::ostream &os, Passenger &p);

typedef std::list<Passenger *> PassengerList;

#endif //CHISS_PASSENGER_H
