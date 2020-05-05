//
// Created by ulf on 3/25/20.
//

#include "gtest/gtest.h"
#include "StandardAlgorithm.h"
#include "ControlPanel.h"
#include "Stop.h"


TEST(StandardAlgoBasic, modulo_tesst)
{
    EXPECT_EQ(modulo(9, 20), 9);
    EXPECT_EQ(modulo(-9, 20), 11);

    EXPECT_EQ(modulo(0, 20), 0);
    EXPECT_EQ(modulo(10, 20), 10);
    EXPECT_EQ(modulo(-10, 20), 10);
    EXPECT_EQ(modulo(22, 20), 2);
    EXPECT_EQ(modulo(-22, 20), 18);
}

TEST(StandardAlgoBasic, mod_tesst)
{
    CarList cars;
    ControlPanel controlPanel;
    StopVector stops;

    Elevator elevator0(0, 10);
    Elevator elevator1(0, 10);

    Car car0(&elevator0);
    Car car1(&elevator1);

    Passenger p1(9, 1);
    Passenger p2(6, 2);
    Passenger p3(3, 5);

    controlPanel.press_floor_buttons(&p1);
    controlPanel.press_floor_buttons(&p2);
    controlPanel.press_car_buttons(&car0, &p3);

    cars.push_back(&car0);
    cars.push_back(&car1);

    // Evaluate
    StandardAlgorithm algo;
    (algo)(cars, controlPanel, stops);

    // Verify
    EXPECT_EQ(stops[0].floor_number_, 5);
}

TEST(StandardAlgoBasic, algo_test_1)
{
    CarList cars;
    ControlPanel controlPanel;
    StopVector stops;

    Elevator elevator0(0, 10);

    Car car0(&elevator0);
    car0.set_current_floor(4, Direction::UP);

    Passenger p1(0, 7);
    Passenger p2(5, 1);

    controlPanel.press_floor_buttons(&p1);
    controlPanel.press_floor_buttons(&p2);

    cars.push_back(&car0);

    // Evaluate
    StandardAlgorithm algo;
    (algo)(cars, controlPanel, stops);

    // Verify
    EXPECT_EQ(stops[0].floor_number_, 5);
}
