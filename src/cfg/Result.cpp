//
// Created by ulf on 8/29/18.
//

#include "Result.h"

Result::Result() = default;

void Result::compute_result(PassengerList &passengers)
{
    number_of_passengers_ = passengers.size();
    passengers_at_destination_ = 0;
    double waiting_time = 0;
    double traveling_time = 0;

    for (const auto &passenger : passengers)
    {
        if (passenger->on_destination())
        {
            waiting_time += passenger->waiting_time();
            traveling_time += passenger->traveling_time();
            passengers_at_destination_ += 1;
        }
    }

    average_traveling_time_ = traveling_time / passengers_at_destination_;
    average_waiting_time_ = waiting_time / passengers_at_destination_;
}

double Result::average_traveling_time() const
{
    return average_traveling_time_;
}

double Result::average_waiting_time() const
{
    return average_waiting_time_;
}

size_t Result::number_of_passengers() const
{
    return number_of_passengers_;
}

size_t Result::passengers_at_destination() const
{
    return passengers_at_destination_;
}

std::ostream &operator<<(std::ostream &os, Result &result)
{
    os <<
       "Number of passengers:     " << result.number_of_passengers() << std::endl <<
       "Passengers at destination:" << result.passengers_at_destination() << std::endl <<
       // "Total simulation time:    " << result.simulation_time() << std::endl <<
       "Average waiting time:     " << result.average_waiting_time() << std::endl <<
       "Average traveling time:   " << result.average_traveling_time() << std::endl;

    return os;
}
