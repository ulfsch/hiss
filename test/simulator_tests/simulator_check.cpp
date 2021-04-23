//
// simulator_check.cpp
//

#include "gtest/gtest.h"
#include "Simulator.h"
#include "StandardAlgorithm.h"


class SingleTraffic : public Traffic
{
public:
    Passenger *operator()(Building *, MilliSeconds time) override
    {
        if (count_ >= no_of_passengers_)
        {
            return nullptr;
        }
        count_ += 1;
        return new Passenger(0, 1, time);
    }

    bool done() const override
    {
        return count_ >= no_of_passengers_;
    }

private:
    const size_t no_of_passengers_ = 1;
    size_t count_ = 0;
};


TEST(SimulatorBasic, one_passener_two_floors)
{
    const FloorNumber FLOORS = 2;
    SingleTraffic traffic;
    StandardAlgorithm algorithm;
    Building building(FLOORS);
    Elevator elevator(0, FLOORS);
    building.add_elevator(&elevator);

    Simulator *simulator = new Simulator(&traffic, &algorithm, &building);
    const ControlPanel &cp = simulator->control_panel();
    Car *car = simulator->cars().front();

    EXPECT_EQ(false, simulator->done());

    MilliSeconds time = 0;

    simulator->tick(time);        // time=0, passenger arrives and enter elevator
    time += SIMULATION_RATE;
    EXPECT_FALSE(simulator->done());
    // EXPECT_EQ(1, cp.car_target_buttons.at(car).count(1));
    // EXPECT_EQ(0, cp.floor_destination_buttons.count(1));
    EXPECT_EQ(0, cp.floor_up_buttons.count(0));
    EXPECT_EQ(0, cp.floor_down_buttons.count(1));
    EXPECT_EQ(0, car->next_floor());

    simulator->tick(time);        // time=1000, move elevator to destination floor
    time += SIMULATION_RATE;
    EXPECT_FALSE(simulator->done());
    // EXPECT_EQ(1, cp.car_target_buttons.at(car).count(1));
    // EXPECT_EQ(0, cp.floor_destination_buttons.count(1));
    EXPECT_EQ(0, cp.floor_up_buttons.count(0));
    EXPECT_EQ(0, cp.floor_down_buttons.count(1));

    simulator->tick(time);        // time=2000, elevator on destination floor, passenger done
    time += SIMULATION_RATE;
    // EXPECT_TRUE(simulator->done());
    //EXPECT_EQ(0, cp.floor_destination_buttons.count(1));
    EXPECT_EQ(0, cp.floor_up_buttons.count(0));
    EXPECT_EQ(0, cp.floor_down_buttons.count(1));
    EXPECT_EQ(1, car->next_floor());

    simulator->tick(time);        // time=3000, elevator idle
    time += SIMULATION_RATE;

    simulator->tick(time);        // time=4000, elevator idle
    time += SIMULATION_RATE;
    simulator->tick(time);        // time=5000, elevator idle
    time += SIMULATION_RATE;
    simulator->tick(time);        // time=6000, elevator idle
    time += SIMULATION_RATE;
    EXPECT_TRUE(simulator->done());

    EXPECT_FALSE(simulator->passengers().front()->on_start_floor());
    EXPECT_TRUE(simulator->passengers().front()->on_destination());
    EXPECT_EQ(1000, simulator->passengers().front()->waiting_time());
    EXPECT_EQ(4000, simulator->passengers().front()->traveling_time());

    delete simulator;
}
