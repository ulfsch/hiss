//
// Passenger.cpp
//
#include "Passenger.h"
#include <cassert>
#include <Floor.h>

Id Passenger::last_id_ = 0;

/**
 *
 * @param begin_floor
 * @param end_floor
 * @param time
 */
Passenger::Passenger(FloorNumber begin_floor, FloorNumber end_floor, Time time) :
        id_(++last_id_),
        begin_floor_(begin_floor),
        end_floor_(end_floor),
        car_(nullptr),
        begin_time_(time),
        pick_up_time_(0),
        end_time_(0)
{
    if (begin_floor_ == end_floor_)
    {
        exit(99);
    }
    assert(begin_floor_ != end_floor_);
}

Id Passenger::id() const
{
    return id_;
}

FloorNumber Passenger::begin_floor() const
{
    return begin_floor_;
}

FloorNumber Passenger::end_floor() const
{
    return end_floor_;
}

Car *Passenger::car() const
{
    return car_;
}

bool Passenger::on_destination() const
{
    return end_time_ != 0;
}

bool Passenger::on_start_floor() const
{
    return pick_up_time_ == 0;
}

void Passenger::set_start_traveling(Car *car, Time time)
{
    assert(pick_up_time_ == 0);
    assert(end_time_ == 0);
    pick_up_time_ = time;
    car_ = car;
}

void Passenger::set_on_destination(Time time)
{
    assert(pick_up_time_ != 0);
    assert(end_time_ == 0);
    end_time_ = time;
    car_ = nullptr;
}

Duration Passenger::waiting_time() const
{
    return (pick_up_time_ > 0) ? pick_up_time_ - begin_time_ : 0;
}

Duration Passenger::traveling_time() const
{
    return (end_time_ > 0) ? end_time_ - pick_up_time_ : 0;
}

int Passenger::print() const
{
    return printf("p(%d->%d) ",
                  begin_floor_,
                  end_floor_);
}

std::ostream &operator<<(std::ostream &os, Passenger &p)
{
    os << std::string("p") << p.id() << "(" << p.begin_floor() << "->" << p.end_floor() << ") ";
    return os;
}
