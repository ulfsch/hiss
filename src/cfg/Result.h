//
// Created by ulf on 8/29/18.
//

#ifndef CHISS_RESULT_H
#define CHISS_RESULT_H


#include <Passenger.h>

class Result
{
public:
    Result();

    void compute_result(PassengerList& passengers);

    double average_traveling_time() const;
    double average_waiting_time() const;
    size_t number_of_passengers() const;
    size_t passengers_at_destination() const;

private:
    double average_traveling_time_ = 0;
    double average_waiting_time_ = 0;
    size_t number_of_passengers_ = 0;
    size_t passengers_at_destination_ = 0;

};

std::ostream &operator<<(std::ostream &os, Result &result);

#endif //CHISS_RESULT_H
