//
// elevator_check.cpp.
//

#include "gtest/gtest.h"
#include "Car.h"
#include "Elevator.h"

/*
 * move_up - move car at constant speed (2 m/s)
 */
TEST(CarBasic, move_up_) {
    Elevator e(10, 20);
    Car car(&e);
    EXPECT_TRUE(car.is_idle_on_floor(10));
    car.set_next_floor(15);
    MilliSeconds ms = 0;

    car.tick(ms); ms += 1000;;
    car.tick(ms); ms += 1000;;
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(10, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(17));

    car.tick(ms); ms += 1000;;
    car.tick(ms); ms += 1000;;
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(10, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(ms); ms += 1000;;
    car.tick(ms); ms += 1000;;
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(10, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(ms); ms += 1000;;
    car.tick(ms); ms += 1000;;
    EXPECT_FALSE(car.is_idle());
    EXPECT_EQ(10, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(ms); ms += 1000;;
    car.tick(ms); ms += 1000;;
    EXPECT_FALSE(car.is_idle());  // state WAIT
    EXPECT_EQ(10, car.current_floor());
    EXPECT_FALSE(car.is_idle_on_floor(15));

    car.tick(ms); ms += 1000;;
    car.tick(ms); ms += 1000;;
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

