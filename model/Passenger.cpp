//
// Passenger.cpp
//
#include <cassert>
#include "Passenger.h"
#include "algorithm"

std::list<Passenger *> Passenger::all_passengers_;
Id Passenger::last_id_ = 0;


Passenger::Passenger(FloorNumber begin_floor, FloorNumber end_floor, Time time) :
        id_(++last_id_),
        begin_floor_(begin_floor),
        end_floor_(end_floor),
        begin_time_(time),
        pick_up_time_(0),
        end_time_(0) {
}

Passenger *Passenger::create(FloorNumber begin_floor, FloorNumber end_floor, Time time) {
    auto *p = new Passenger(begin_floor, end_floor, time);
    all_passengers_.push_back(p);
    return p;
}

Id Passenger::id() const {
    return id_;
}

FloorNumber Passenger::begin_floor() const {
    return begin_floor_;
}

FloorNumber Passenger::end_floor() const {
    return end_floor_;
}

bool Passenger::on_end_floor(FloorNumber i) const {
    return end_floor_ == i;
}

bool Passenger::on_begin_floor(FloorNumber floor_number) const {
    return begin_floor_ == floor_number;
}

void Passenger::set_start_traveling(Time time) {
    assert(pick_up_time_ == 0);
    assert(end_time_ == 0);
    pick_up_time_ = time;
}

void Passenger::set_on_destination(Time time) {
    assert(pick_up_time_ != 0);
    assert(end_time_ == 0);
    end_time_ = time;
}

Duration Passenger::waiting_time() const {
    return (pick_up_time_ > 0) ? pick_up_time_ - begin_time_ : 0;
}

Duration Passenger::traveling_time() const {
    return (end_time_ > 0) ? end_time_ - pick_up_time_ : 0;
}

void Passenger::delete_all() {
    for (Passenger *p : all_passengers_) {
        delete p;
    }
    all_passengers_.clear();
}

Duration Passenger::average_waiting_time() {
    if (all_passengers_.empty()) {
        return 0;
    }

    double sum = 0L;
    size_t count = 0;
    for (Passenger *p : all_passengers_) {
        if (p->pick_up_time_ > 0) {
            sum += p->waiting_time();
            count += 1;
        }
    }

    return sum / count;
}

Duration Passenger::average_traveling_time() {
    if (all_passengers_.empty()) {
        return 0;
    }
    double sum = 0L;
    size_t count = 0;
    for (Passenger *p : all_passengers_) {
        if (p->end_time_ > 0) {
            sum += p->traveling_time();
            count += 1;
        }
    }

    return sum / count;
}

bool Passenger::all_at_destination() {
    for (Passenger *p : all_passengers_) {
        if (p->end_time_ == 0) {
            return false;
        }
    }
    return true;
}

PassengerList &Passenger::all_passengers() {
    return all_passengers_;
}

std::ostream &operator<<(std::ostream &os, Passenger &p) {
    os << std::string("p") << p.id() << "(" << p.begin_floor() << "-" << p.end_floor() << ")";
    return os;
}
