//
// Created by ulf on 8/29/18.
//

#ifndef CHISS_RESULT_H
#define CHISS_RESULT_H


#include "Simulator.h"
#include "Passenger.h"

class Result
{
public:
    Result();

    void compute_result(Time time, PassengerList &passengers);

    Time simulation_time() const;
    double average_traveling_time() const;
    double average_waiting_time() const;
    size_t number_of_passengers() const;
    size_t passengers_at_destination() const;

private:
    Time simulation_time_ = 0;
    double average_traveling_time_ = 0;
    double average_waiting_time_ = 0;
    size_t number_of_passengers_ = 0;
    size_t passengers_at_destination_ = 0;

};

std::ostream &operator<<(std::ostream &os, const Result &result);

#endif //CHISS_RESULT_H
