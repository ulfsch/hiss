//
// elevator_check.cpp.
//

#include "gtest/gtest.h"
#include "Car.h"
#include "Elevator.h"
#include "Direction.h"

/*
 * move_up - move car at constant speed (2 m/s)
 */
TEST(CarBasic, move_up_) {
    Elevator e(10, 20);
    Car car(&e);
    EXPECT_TRUE(car.is_idle_on_floor(10));
    car.set_next_floor(15);

    car.tick(1);
    car.tick(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(11, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(17));

    car.tick(1);
    car.tick(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(12, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(1);
    car.tick(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(13, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(1);
    car.tick(1);
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(14, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(1);
    car.tick(1);
    EXPECT_FALSE(car.is_idle());  // state WAIT
    EXPECT_EQ(15, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(1);
    car.tick(1);
    EXPECT_TRUE(car.is_idle());  // state IDLE
    EXPECT_EQ(15, car.current_floor());
    EXPECT_TRUE(car.is_idle_on_floor(15));

}

/**
 * Test out of range
 */
TEST(CarBasic, move_error_cases) {
    Elevator e(10, 14);
    Car car(&e);

    ASSERT_DEATH(car.set_next_floor(14), "");
    EXPECT_TRUE(car.is_idle_on_floor(10));

}

