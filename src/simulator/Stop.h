//
// Created by ulf on 8/31/19.
//

#ifndef CHISS_STOP_H
#define CHISS_STOP_H

#include <common.h>
#include <Direction.h>
#include <Elevator.h>


class Stop
{
public:
    Stop(Elevator *e, FloorNumber n, Direction d = Direction::NONE) :
            elevator(e),
            floor(n),
            direction(d)
    {
        in_elevator_direction_ = (d == e->direction());
        in_travel_direction_ = (d == e->direction());
        distance_ = std::abs(n - e->current_floor());
    }

    bool operator<(const Stop &b) const;

public:
    Elevator *elevator;
    FloorNumber floor;
    Direction direction;

private:
    bool in_elevator_direction_;
    bool in_travel_direction_;
    FloorNumber distance_;

};


#endif //CHISS_STOP_H
