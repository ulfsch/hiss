//
// ConstantTraffic.h.
//
#ifndef CHISS_CONSTANTTRAFFIC_H
#define CHISS_CONSTANTTRAFFIC_H

#include "Traffic.h"

class ConstantTraffic : public Traffic
{
public:
    ConstantTraffic(size_t number_of_floors, size_t total_no_of_passengers, double rate);

    PassengerList operator()(Time time) override;

    bool done() const override;

private:
    const size_t number_of_floors_;
    const size_t max_no_of_passengers_;
    const double rate_;

    size_t no_of_passengers_;
    double count_;
};

#endif //CHISS_CONSTANTTRAFFIC_H
