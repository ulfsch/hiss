//
// Simulator.h.
//
#ifndef CHISS_SIMULATOR_H
#define CHISS_SIMULATOR_H

#include "Algorithm.h"
#include "Building.h"
#include "Car.h"
#include "Passenger.h"
#include "Traffic.h"
#include "ControlPanel.h"


class Simulator
{
public:
    explicit Simulator(Traffic *traffic, Algorithm *algorithm, Building *building);
    virtual ~Simulator();

    void simulation_step(Time simulation_time, Duration real_time);
    bool done() const;

    Building *building() const { return building_; }
    const PassengerList &passengers() const { return passengers_; }
    const CarList &cars() const { return cars_; }

private:
    void move_passengers(Time time);

private:
    Traffic *traffic_generator_;
    Algorithm *algorithm_;
    Building *building_;

    PassengerList passengers_;
    CarList cars_;
    ControlPanel control_panels_;

};

#endif //CHISS_SIMULATOR_H
