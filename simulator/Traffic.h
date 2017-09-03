//
// Traffic.h.
//
#ifndef CHISS_TRAFFIC_H
#define CHISS_TRAFFIC_H

#include "../model/common.h"

class Passenger;

class Traffic
{
public:
    virtual ~Traffic() = default;
    virtual Passenger* operator()(Time) = 0;
    virtual bool done() const = 0;

};

#endif //CHISS_TRAFFIC_H
