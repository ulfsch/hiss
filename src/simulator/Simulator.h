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


class Simulator
{
public:
    explicit Simulator(Traffic *traffic, Algorithm *algorithm, Building *building);
    virtual ~Simulator();

    void tick(Time time, Duration dt);
    bool done() const;

    Building *building() const
    { return building_; }
    const PassengerList &passengers() const { return passengers_; }

    const CarList &cars() const
    { return cars_; }

    void inject_passenger(Passenger *passenger);
    void inject_cars();

private:
    void move_passengers(Time time);
    void move_cars(Duration dt);

private:
    Traffic *traffic_generator_;
    Algorithm *algorithm_;
    Building *building_;

    PassengerList passengers_;
    CarList cars_;

};

#endif //CHISS_SIMULATOR_H
