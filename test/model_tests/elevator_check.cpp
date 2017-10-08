//
// elevator_check.cpp.
//

#include "gtest/gtest.h"
#include "../../model/Elevator.h"

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
    EXPECT_FALSE(e.is_idle()); // Waiting
    EXPECT_EQ(17, e.current_floor());
    EXPECT_FALSE(e.standing_on_floor(17));

    e.move(1);
    EXPECT_TRUE(e.is_idle());
    EXPECT_EQ(17, e.current_floor());
    EXPECT_TRUE(e.standing_on_floor(17));

    // New target (15)

    e.move(1);
    EXPECT_FALSE(e.is_idle());
    EXPECT_EQ(15, e.current_floor());
    EXPECT_FALSE(e.standing_on_floor(15));

    e.move(1);
    EXPECT_TRUE(e.is_idle());
    EXPECT_EQ(15, e.current_floor());
    EXPECT_TRUE(e.standing_on_floor(15));

}

TEST(ElevatorBasic, move2) {
    FloorNumber floor_array[] = {10, 20, 21, 22};
    Elevator e(floor_array, 4);
    EXPECT_TRUE(e.standing_on_floor(10));

    e.go_to(21);

    e.move(1);
    EXPECT_FALSE(e.is_idle());
    EXPECT_EQ(11, e.current_floor());
    EXPECT_FALSE(e.standing_on_floor(17));

    e.move(1);
    EXPECT_EQ(12, e.current_floor());
    e.move(1);
    EXPECT_EQ(13, e.current_floor());
    e.move(1);
    EXPECT_EQ(15, e.current_floor());
    e.move(1);
    EXPECT_EQ(16, e.current_floor());
    e.move(1);
    EXPECT_EQ(17, e.current_floor());
    e.move(1);
    EXPECT_EQ(18, e.current_floor());
    e.move(1);
    EXPECT_EQ(20, e.current_floor());
    e.move(1);
    EXPECT_EQ(21, e.current_floor());
    e.move(1);
    EXPECT_TRUE(e.is_idle());
    EXPECT_EQ(21, e.current_floor());
    EXPECT_TRUE(e.standing_on_floor(21));

}

TEST(ElevatorBasic, butttons) {
    Elevator e(10, 20, 12);
    EXPECT_TRUE(e.buttons().empty());

    Passenger *p1 = new Passenger(3, 7, 0);
    e.press_floor_button(p1->end_floor());
    EXPECT_TRUE(e.buttons().count(7) == 1);

    e.clear_floor_button(7);
    EXPECT_TRUE(e.buttons().empty());

    delete p1;
}
