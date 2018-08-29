//
// Simulator.h.
//
#ifndef CHISS_SIMULATOR_H
#define CHISS_SIMULATOR_H

#include "Configuration.h"
#include "Building.h"
#include "Traffic.h"
#include "Algorithm.h"

class Simulator {
public:
    explicit Simulator(Configuration &configuration);
    void execute(Time time, Duration dt);
    bool done() const;

    void end(Time time);

    Building &building() { return building_; }

private:
    void inject_passenger(std::shared_ptr<Passenger> passenger);
    void move_passengers(Time time);
    void disembark(Elevator &elevator, Time time);
    void embark(Floor &floor, Elevator &elevator, Time time);
    void move_elevators(Duration dt);

private:
    Result &result_;
    Traffic &traffic_generator_;
    Algorithm &algorithm_;
    Building &building_;
    PassengerList passengers_;
};

std::ostream &operator<<(std::ostream &os, Simulator &);

#endif //CHISS_SIMULATOR_H
