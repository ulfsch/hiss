//
// Traffic.h.
//
#ifndef CHISS_TRAFFIC_H
#define CHISS_TRAFFIC_H

#include "common.h"

class Building;

class Passenger;

class Traffic
{
public:
    virtual ~Traffic() = default;

    virtual Passenger *operator()(Building *building, MilliSeconds) = 0;

    virtual bool done() const = 0;

};

#endif //CHISS_TRAFFIC_H
