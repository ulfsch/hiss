//
// Traffic.h.
//
#ifndef CHISS_TRAFFIC_H
#define CHISS_TRAFFIC_H

#include "../model/common.h"
#include "../model/Passenger.h"

class Traffic
{
public:
    virtual ~Traffic() = default;
    virtual PassengerList operator()(Time) = 0;
    virtual bool done() const = 0;

};

#endif //CHISS_TRAFFIC_H
