//
// Passenger.h
//
#ifndef CHISS_PASSENGER_H
#define CHISS_PASSENGER_H

#include "common.h"
#include <list>
#include <ostream>

class Passenger;

typedef std::list<Passenger *> PassengerList;


class Passenger {
    Passenger(FloorNumber begin_floor, FloorNumber end_floor, Time time);

public:
    Passenger(const Passenger &b) = delete;
    static Passenger *create(FloorNumber begin_floor, FloorNumber end_floor, Time time);

    Id id() const;
    FloorNumber begin_floor() const;
    FloorNumber end_floor() const;
    bool on_end_floor(FloorNumber i) const;
    bool on_begin_floor(FloorNumber floor_number) const;

    Duration waiting_time() const;
    Duration traveling_time() const;

    void set_start_traveling(Time time);
    void set_on_destination(Time time);

    static Duration average_waiting_time();
    static Duration average_traveling_time();
    static bool all_at_destination();
    static void delete_all();
    static PassengerList &all_passengers();

private:
    static Id last_id_;
    Id id_;

    FloorNumber begin_floor_;
    FloorNumber end_floor_;

    Time begin_time_;
    Time pick_up_time_;
    Time end_time_;

    static PassengerList all_passengers_;

};

std::ostream &operator<<(std::ostream &os, Passenger &p);

#endif //CHISS_PASSENGER_H
