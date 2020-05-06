//
// Created by ulf on 8/31/19.
//

#ifndef CHISS_STOP_H
#define CHISS_STOP_H

#include "common.h"
#include "Car.h"


class Stop
{
public:
    Stop(FloorNumber floor_number, Direction direction, Car *car);

    bool operator<(const Stop &b) const;
    bool operator==(const Stop &b) const;

    Car *car() const { return  car_; }

public:
    FloorNumber floor_number_;
    Car *car_;
    int distance_;

};

typedef std::vector<Stop> StopVector;

#endif //CHISS_STOP_H
