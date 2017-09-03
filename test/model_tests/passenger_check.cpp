//
// passenger_test.cpp
//

#include "gtest/gtest.h"
#include "../../model/Passenger.h"

TEST(PassengerBasic, access_methods) {
    Passenger* p = Passenger::create(7, 14, 10);
    EXPECT_EQ(7, p->begin_floor());
    EXPECT_EQ(14, p->end_floor());
    
    EXPECT_FALSE(p->on_begin_floor(8));
    EXPECT_TRUE(p->on_begin_floor(7));
    EXPECT_FALSE(p->on_end_floor(13));
    EXPECT_TRUE(p->on_end_floor(14));

    Passenger::delete_all();
}

TEST(PassengerBasic, waiting_time) {
    Time time = 50;
    EXPECT_TRUE(Passenger::all_at_destination());
    EXPECT_EQ(0, Passenger::average_waiting_time());

    Passenger* p = Passenger::create(7, 14, time);
    p->set_start_traveling(time + 8);
    EXPECT_EQ(8, p->waiting_time());
    EXPECT_EQ(8, Passenger::average_waiting_time());

    p = Passenger::create(8, 15, time+100);
    p->set_start_traveling(time + 116);
    EXPECT_FALSE(Passenger::all_at_destination());
    EXPECT_EQ(16, p->waiting_time());
    EXPECT_EQ(12, Passenger::average_waiting_time());

    p = Passenger::create(8, 16, time+1110);
    EXPECT_FALSE(Passenger::all_at_destination());
    EXPECT_EQ(0, p->waiting_time());
    EXPECT_EQ(12, Passenger::average_waiting_time());

    Passenger::delete_all();
}

TEST(PassengerBasic, traveling_time) {
    Time time = 50;
    EXPECT_EQ(0, Passenger::average_traveling_time());

    Passenger* p = Passenger::create(7, 14, time);
    p->set_start_traveling(time + 8);
    p->set_on_destination(time + 18);
    EXPECT_TRUE(Passenger::all_at_destination());
    EXPECT_EQ(10, p->traveling_time());
    EXPECT_EQ(10, Passenger::average_traveling_time());

    p = Passenger::create(8, 15, time+100);
    p->set_start_traveling(time + 108);
    p->set_on_destination(time + 114);
    EXPECT_TRUE(Passenger::all_at_destination());
    EXPECT_EQ(6, p->traveling_time());
    EXPECT_EQ(8, Passenger::average_traveling_time());

    Passenger::delete_all();
}
