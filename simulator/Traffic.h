//
// Traffic.h.
//
#ifndef CHISS_TRAFFIC_H
#define CHISS_TRAFFIC_H


class Traffic
{
public:
    virtual ~Traffic() {}
    virtual Passenger* operator()(Time) = 0;
};

#endif //CHISS_TRAFFIC_H
