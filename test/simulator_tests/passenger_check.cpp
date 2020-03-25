//
// passenger_test.cpp
//

#include "gtest/gtest.h"
#include "Passenger.h"
#include "Car.h"
#include "Elevator.h"
#include "Floor.h"

static Floor floor_7(7);
static Floor floor_8(8);
static Floor floor_14(14);
static Floor floor_15(15);
static Elevator elevator(0, 10);
static Car car(&elevator);

TEST(PassengerBasic, access_methods) {
    Passenger *p = new Passenger(7, 14, 10);
    EXPECT_EQ(7, p->begin_floor());
    EXPECT_EQ(14, p->end_floor());

    delete p;
}

TEST(PassengerBasic, waiting_time) {
    Time time = 50;
    Passenger *p = new Passenger(7, 14, time);
    p->set_start_traveling(&car, time + 8);
    EXPECT_EQ(8UL, p->waiting_time());

    Passenger *p2 = new Passenger(8, 15, time + 100);
    p2->set_start_traveling(&car, time + 116);
    EXPECT_FALSE(p2->on_destination());
    EXPECT_EQ(16UL, p2->waiting_time());

    delete p;
    delete p2;
}

TEST(PassengerBasic, traveling_time) {
    Time time = 50;
    Passenger *p = new Passenger(7, 14, time);
    p->set_start_traveling(&car, time + 8);
    p->set_on_destination(time + 18);
    EXPECT_TRUE(p->on_destination());
    EXPECT_EQ(10U, p->traveling_time());

    delete p;
}
