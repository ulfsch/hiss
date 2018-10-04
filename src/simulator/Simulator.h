//
// Simulator.h.
//
#ifndef CHISS_SIMULATOR_H
#define CHISS_SIMULATOR_H

#include "Algorithm.h"
#include "Building.h"
#include "Result.h"
#include "Traffic.h"

class Simulator
{
public:
    explicit Simulator(Traffic *traffic, Algorithm *algorithm, Building *building);

    void tick(Time time, Duration dt);
    bool done() const;

    Building *building() const
    { return building_; }

    PassengerList &passengers()
    { return passengers_; }

private:
    void inject_passenger(std::shared_ptr<Passenger> passenger);
    void move_passengers(Time time);
    void disembark(Elevator *elevator, Time time);
    void embark(Floor *floor, Elevator *elevator, Time time);
    void move_elevators(Duration dt);

private:
    Traffic *traffic_generator_;
    Algorithm *algorithm_;
    Building *building_;
    PassengerList passengers_;

};

std::ostream &operator<<(std::ostream &os, Simulator &);

#endif //CHISS_SIMULATOR_H
