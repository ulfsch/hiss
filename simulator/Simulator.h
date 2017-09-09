//
// Simulator.h.
//
#ifndef CHISS_SIMULATOR_H
#define CHISS_SIMULATOR_H

#include "../model/Building.h"
#include "Traffic.h"
#include "Algorithm.h"

class Simulator {
public:
    Simulator(Traffic &traffic, Algorithm &algorithm, Building &building);
    void step(Time time, Duration dt);
    bool done() const;

    Building &building() { return building_; }

private:
    void inject_passenger(Passenger *passenger);
    void move_passengers(Time time);
    void disembark(Elevator &elevator, Floor &floor, Time time);
    void embark(Floor &floor, Elevator &elevator, Time time);
    void move_elevators(Duration dt);

private:
    Traffic &traffic_;
    Algorithm &algorithm_;
    Building &building_;

};

std::ostream &operator<<(std::ostream &os, Simulator &);

#endif //CHISS_SIMULATOR_H
