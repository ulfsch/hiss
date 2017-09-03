//
// elevator_check.cpp.
//

#include "gtest/gtest.h"
#include "../../model/Elevator.h"

TEST(ElevatorBasic, access_methods) {
    Elevator e(10, 20);
    EXPECT_EQ(10, e.current_floor());
    EXPECT_TRUE(e.is_idle());
}

TEST(ElevatorBasic, move) {
    Elevator e(10, 20, 12);
    EXPECT_TRUE(e.standing_on_floor(10));
    e.go_to(17);

    e.move(1);
    EXPECT_FALSE(e.is_idle());
    EXPECT_EQ(13, e.current_floor());
    EXPECT_FALSE(e.standing_on_floor(17));

    e.go_to(15);

    e.move(1);
    EXPECT_FALSE(e.is_idle());
    EXPECT_EQ(16, e.current_floor());
    EXPECT_FALSE(e.standing_on_floor(17));

    e.move(1);
    EXPECT_TRUE(e.is_idle());
    EXPECT_EQ(17, e.current_floor());
    EXPECT_TRUE(e.standing_on_floor(17));

    // New target (15)

    e.move(1);
    EXPECT_TRUE(e.is_idle());
    EXPECT_EQ(15, e.current_floor());
    EXPECT_TRUE(e.standing_on_floor(15));

}
