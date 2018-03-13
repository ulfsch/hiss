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
    Car car(10, 12, 4);
    EXPECT_TRUE(car.is_idle_on_floor(10));
    car.set_next_floor(17);

    car.move(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(13, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(17));

    car.set_next_floor(15);

    car.move(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(16, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(17));

    car.move(1);
    EXPECT_FALSE(car.is_idle()); // Waiting
    EXPECT_EQ(17, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(17));

    car.move(1);
    EXPECT_TRUE(car.is_idle());
    EXPECT_EQ(17, car.current_floor());
    EXPECT_TRUE(car.is_idle_on_floor(17));

    // New target (15)

    car.move(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(15, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.move(1);
    EXPECT_TRUE(car.is_idle());
    EXPECT_EQ(15, car.current_floor());
    EXPECT_TRUE(car.is_idle_on_floor(15));

}

TEST(ElevatorBasic, move2) {
    Car car(10, 5, 4);
    EXPECT_TRUE(car.is_idle_on_floor(10));

    car.set_next_floor(21);

    car.move(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(11, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(17));

    car.move(1);
    EXPECT_EQ(12, car.current_floor());
    car.move(1);
    EXPECT_EQ(13, car.current_floor());
    car.move(1);
    EXPECT_EQ(15, car.current_floor());
    car.move(1);
    EXPECT_EQ(16, car.current_floor());
    car.move(1);
    EXPECT_EQ(17, car.current_floor());
    car.move(1);
    EXPECT_EQ(18, car.current_floor());
    car.move(1);
    EXPECT_EQ(20, car.current_floor());
    car.move(1);
    EXPECT_EQ(21, car.current_floor());
    car.move(1);
    EXPECT_TRUE(car.is_idle());
    EXPECT_EQ(21, car.current_floor());
    EXPECT_TRUE(car.is_idle_on_floor(21));

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
