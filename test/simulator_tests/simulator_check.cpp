//
// simulator_check.cpp
//

#include "gtest/gtest.h"
#include "Simulator.h"
#include "UpDownButtonAlgorithm.h"


class SingleTraffic : public Traffic
{
public:
    Passenger * operator()(Building *building, Time time) override
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


TEST(SimulatorBasic, one_passener_two_floors) {
    const FloorNumber FLOORS = 2;
    SingleTraffic traffic;
    UpDownButtonAlgorithm algorithm;
    Building building(FLOORS);
    Elevator elevator(0, FLOORS);
    building.add_elevator(&elevator);

    Simulator *simulator = new Simulator(&traffic, &algorithm,  &building);
    EXPECT_EQ(false, simulator->done());
    EXPECT_EQ(0, elevator.destination_buttons().count(0));
    EXPECT_EQ(0, elevator.destination_buttons().count(1));

    Time time = 0;

    simulator->tick(++time, 1);        // time=1, passenger arrives and enter elevator
    EXPECT_FALSE(simulator->done());
    EXPECT_EQ(1, elevator.destination_buttons().count(1));
    EXPECT_FALSE(building.floor(0)->up_button());
    EXPECT_FALSE(building.floor(0)->down_button());
    EXPECT_EQ(1, elevator.next_floor());

    simulator->tick(++time, 1);        // time=2, move elevator to destination floor
    EXPECT_FALSE(simulator->done());
    // EXPECT_EQ(1, elevator.destination_buttons().count(1));
    EXPECT_FALSE(building.floor(0)->up_button());
    EXPECT_FALSE(building.floor(0)->down_button());
    EXPECT_EQ(1, elevator.next_floor());

    simulator->tick(++time, 1);        // time=3, elevator on destination floor, passenger done
    EXPECT_TRUE(simulator->done());
    EXPECT_EQ(0, elevator.destination_buttons().count(1));
    EXPECT_FALSE(building.floor(0)->up_button());
    EXPECT_FALSE(building.floor(0)->down_button());
    EXPECT_EQ(1, elevator.next_floor());

    simulator->tick(++time, 1);        // elevator idle
    EXPECT_TRUE(simulator->done());

    EXPECT_FALSE(simulator->passengers().front()->on_start_floor());
    EXPECT_TRUE(simulator->passengers().front()->on_destination());
    EXPECT_EQ(0, simulator->passengers().front()->waiting_time());
    EXPECT_EQ(2, simulator->passengers().front()->traveling_time());

    delete simulator;
}
