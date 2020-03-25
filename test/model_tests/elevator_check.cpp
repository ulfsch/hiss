//
// elevator_check.cpp.
//

#include "gtest/gtest.h"
#include "Elevator.h"
#include "Direction.h"

TEST(ElevatorBasic, direction) {
    Direction a = Direction::DOWN;
    Direction b = Direction::DOWN;
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(Direction::UP == Direction::UP);
    EXPECT_TRUE(Direction::DOWN == Direction::DOWN);

    EXPECT_TRUE(Direction::DOWN == Direction::NONE);
    EXPECT_TRUE(Direction::UP == Direction::NONE);
    EXPECT_TRUE(Direction::NONE == Direction::DOWN);
    EXPECT_TRUE(Direction::NONE == Direction::UP);

    EXPECT_FALSE(Direction::DOWN == Direction::UP);
    EXPECT_FALSE(Direction::UP == Direction::DOWN);
}
