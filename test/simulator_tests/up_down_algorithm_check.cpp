//
// up_down_algorithm_check.cpp.
//

#include "gtest/gtest.h"
#include "Building.h"
#include "UpDownButtonAlgorithm.h"

static const FloorNumber NUMBER_OF_FLOORS = 10;


class UpDownAlgorithm : public ::testing::Test {

protected:
    virtual void SetUp() {
        building.add_elevator(new Elevator(0, NUMBER_OF_FLOORS));
    }

public:
    Building building{NUMBER_OF_FLOORS};
    UpDownButtonAlgorithm algorithm;

};

TEST_F(UpDownAlgorithm, basic1) {
    Elevator *elevator = building.elevators().front();

    elevator->press_destination_button(7);
    building.floors()[5]->press_buttons(3);
    algorithm(&building);
    EXPECT_EQ(7, elevator->car().next_floor());
}

TEST_F(UpDownAlgorithm, basic2) {
    Elevator *elevator = building.elevators().front();

    elevator->press_destination_button(7);
    building.floors()[5]->press_buttons(9);
    algorithm(&building);
    EXPECT_EQ(5, elevator->car().next_floor());
}

TEST_F(UpDownAlgorithm, preferElevatorDirection) {
    Elevator *elevator = building.elevators().front();

    elevator->car().set_position(7, Direction::UP);
    building.floors()[9]->press_buttons(3);
    building.floors()[6]->press_buttons(3);
    algorithm(&building);
    EXPECT_EQ(9, elevator->car().next_floor());
}

TEST_F(UpDownAlgorithm, SameDir) {
    Elevator *elevator = building.elevators().front();

    elevator->car().set_position(5, Direction::UP);
    building.floors()[7]->press_buttons(10);
    building.floors()[9]->press_buttons(3);
    algorithm(&building);
    EXPECT_EQ(7, elevator->car().next_floor());
}

TEST_F(UpDownAlgorithm, OppositeDir) {
    Elevator *elevator = building.elevators().front();

//    elevator->car().set_position(5, Direction::UP);
//    building.floors()[7]->press_buttons(3);
//    building.floors()[9]->press_buttons(3);
//    algorithm(&building);
//    EXPECT_EQ(9, elevator->car().next_floor());

    elevator->car().set_position(5, Direction::UP);
    elevator->press_destination_button(7);
    building.floors()[9]->press_buttons(3);
    algorithm(&building);
    EXPECT_EQ(7, elevator->car().next_floor());
}

TEST_F(UpDownAlgorithm, OppositeDirIdle) {
    Elevator *elevator = building.elevators().front();

//    elevator->car().set_position(5, Direction::NONE);
//    building.floors()[7]->press_buttons(3);
//    building.floors()[9]->press_buttons(3);
//    algorithm(&building);
//    EXPECT_EQ(9, elevator->car().next_floor());

    elevator->car().set_position(5, Direction::NONE);
    elevator->press_destination_button(7);
    building.floors()[9]->press_buttons(3);
    algorithm(&building);
    EXPECT_EQ(7, elevator->car().next_floor());
}

TEST_F(UpDownAlgorithm, OppositeDirDown) {
    Elevator *elevator = building.elevators().front();

//    elevator->car().set_position(5, Direction::DOWN);
//    building.floors()[7]->press_buttons(3);
//    building.floors()[9]->press_buttons(3);
//    algorithm(&building);
//    EXPECT_EQ(9, elevator->car().next_floor());

    elevator->car().set_position(5, Direction::DOWN);
    elevator->press_destination_button(7);
    building.floors()[9]->press_buttons(3);
    algorithm(&building);
    EXPECT_EQ(7, elevator->car().next_floor());
}
