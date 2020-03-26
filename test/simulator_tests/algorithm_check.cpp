//
// Created by ulf on 3/25/20.
//

#include "gtest/gtest.h"
#include "StandardAlgorithm.h"
#include "ControlPanel.h"
#include "Stop.h"


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
    for (auto &stop : stops)
    {
        EXPECT_EQ(stop.floor_number_, 5);
    }

}