//
// ConstantTraffic.h.
//
#ifndef CHISS_CONSTANTTRAFFIC_H
#define CHISS_CONSTANTTRAFFIC_H

#include "../model/Passenger.h"
#include "Traffic.h"

class ConstantTraffic : public Traffic {
public:
    ConstantTraffic(size_t number_of_floors, size_t total_no_of_passengers, double);
    Passenger *operator()(Time time);

    void off();
private:
    size_t number_of_floors_;
    size_t max_no_of_passengers_;
    double passengers_per_tick_;
    size_t no_of_passengers_;
    size_t count_;
};


#endif //CHISS_CONSTANTTRAFFIC_H
