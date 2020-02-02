//
// up_down_algorithm_check.cpp.
//

#include "gtest/gtest.h"
#include "Building.h"
#include "StandardAlgorithm.h"

static const FloorNumber NUMBER_OF_FLOORS = 10;


class StandardAlgoTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        building.add_elevator(new Elevator(0, NUMBER_OF_FLOORS));
    }

public:
    Building building{NUMBER_OF_FLOORS};
    StandardAlgorithm algorithm;

};

TEST_F(StandardAlgoTest, basic1) {
    Elevator *elevator = building.elevators().front();

    elevator->press_destination_button(7);
    building.floors()[5]->press_buttons(3);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(7, result.front().floor_number_);
}

TEST_F(StandardAlgoTest, basic2) {
    Elevator *elevator = building.elevators().front();

    elevator->press_destination_button(7);
    building.floors()[5]->press_buttons(9);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(5, result.front().floor_number_);
}

TEST_F(StandardAlgoTest, preferElevatorDirection) {
    Elevator *elevator = building.elevators().front();

    elevator->set_position(7, Direction::UP);
    building.floors()[9]->press_buttons(3);
    building.floors()[6]->press_buttons(3);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(9, result.front().floor_number_);
}

TEST_F(StandardAlgoTest, SameDir) {
    Elevator *elevator = building.elevators().front();

    elevator->set_position(5, Direction::UP);
    building.floors()[7]->press_buttons(10);
    building.floors()[9]->press_buttons(3);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(7, result.front().floor_number_);
}

TEST_F(StandardAlgoTest, OppositeDir) {
    Elevator *elevator = building.elevators().front();

//    elevator->set_position(5, Direction::UP);
//    building.floors()[7]->press_buttons(3);
//    building.floors()[9]->press_buttons(3);
//    algorithm(&building);
//    EXPECT_EQ(9, result.front().floor);

    elevator->set_position(5, Direction::UP);
    elevator->press_destination_button(7);
    building.floors()[9]->press_buttons(3);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(7, result.front().floor_number_);
}

TEST_F(StandardAlgoTest, OppositeDirIdle) {
    Elevator *elevator = building.elevators().front();

//    elevator->set_position(5, Direction::NONE);
//    building.floors()[7]->press_buttons(3);
//    building.floors()[9]->press_buttons(3);
//    algorithm(&building);
//    EXPECT_EQ(9, result.front().floor);

    elevator->set_position(5, Direction::NONE);
    elevator->press_destination_button(7);
    building.floors()[9]->press_buttons(3);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(7, result.front().floor_number_);
}

TEST_F(StandardAlgoTest, OppositeDirDown) {
    Elevator *elevator = building.elevators().front();

//    elevator->set_position(5, Direction::DOWN);
//    building.floors()[7]->press_buttons(3);
//    building.floors()[9]->press_buttons(3);
//    algorithm(&building);
//    EXPECT_EQ(9, result.front().floor);

    elevator->set_position(5, Direction::DOWN);
    elevator->press_destination_button(7);
    building.floors()[9]->press_buttons(3);
    std::vector<Stop> result;
    algorithm(&building, result);
    EXPECT_EQ(7, result.front().floor_number_);
}
