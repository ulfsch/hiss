//
// passenger_test.cpp
//

#include "gtest/gtest.h"
#include "../../model/Passenger.h"

TEST(PassengerBasic, access_methods) {
    Passenger *p = new Passenger(7, 14, 10);
    EXPECT_EQ(7, p->begin_floor());
    EXPECT_EQ(14, p->end_floor());
    
    EXPECT_FALSE(p->on_begin_floor(8));
    EXPECT_TRUE(p->on_begin_floor(7));
    EXPECT_FALSE(p->on_end_floor(13));
    EXPECT_TRUE(p->on_end_floor(14));

    delete p;
}

TEST(PassengerBasic, waiting_time) {
    Time time = 50;
    Passenger *p = new Passenger(7, 14, time);
    p->set_start_traveling(time + 8);
    EXPECT_EQ(8, p->waiting_time());

    Passenger *p2 = new Passenger(8, 15, time + 100);
    p2->set_start_traveling(time + 116);
    EXPECT_FALSE(p2->on_destination());
    EXPECT_EQ(16, p2->waiting_time());

    delete p;
    delete p2;
}

TEST(PassengerBasic, traveling_time) {
    Time time = 50;
    Passenger *p = new Passenger(7, 14, time);
    p->set_start_traveling(time + 8);
    p->set_on_destination(time + 18);
    EXPECT_TRUE(p->on_destination());
    EXPECT_EQ(10, p->traveling_time());

    delete p;
}
