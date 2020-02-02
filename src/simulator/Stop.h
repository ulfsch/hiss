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
    Stop(Elevator *e, FloorNumber floorNumber, Direction direction = Direction::NONE);
    bool operator<(const Stop &b) const;

public:
    Elevator *elevator_;
    FloorNumber floor_number_;
    Direction travel_direction_;

private:
    bool in_elevator_direction_;
    bool in_travel_direction_;
    FloorNumber distance_;

};


#endif //CHISS_STOP_H
