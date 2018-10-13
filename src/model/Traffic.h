//
// Traffic.h.
//
#ifndef CHISS_TRAFFIC_H
#define CHISS_TRAFFIC_H

#include "common.h"
#include "Passenger.h"

class Traffic
{
public:
    virtual ~Traffic() = default;

    virtual Passenger *operator()(Building *building, Time) = 0;

    virtual bool done() const = 0;

};

#endif //CHISS_TRAFFIC_H
