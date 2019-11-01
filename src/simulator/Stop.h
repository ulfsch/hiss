//
// Created by ulf on 8/31/19.
//

#ifndef CHISS_STOP_H
#define CHISS_STOP_H

#include <common.h>
#include <Car.h>
#include <Direction.h>


class Stop
{
public:
    Stop(Car *car, FloorNumber n, Direction d = Direction::NONE);
    bool operator<(const Stop &b) const;

public:
    Car *car;
    FloorNumber floor;
    Direction direction;

private:
    bool in_elevator_direction_;
    bool in_travel_direction_;
    FloorNumber distance_;

};


#endif //CHISS_STOP_H
