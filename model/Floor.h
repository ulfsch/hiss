//
// Floor.h.
//
#ifndef CHISS_FLOOR_H
#define CHISS_FLOOR_H

#include "Passenger.h"
#include <set>

class Floor {
    void operator=(const Floor &b);
public:
    explicit Floor(FloorNumber floor_number);

    FloorNumber number() const { return number_; }

    PassengerList &passengers() { return passengers_; }

    bool call_button() const { return call_button_; }

    void press_buttons(Passenger *passenger);
    void clear_buttons();

private:
    FloorNumber number_;
    PassengerList passengers_;

    // Single call button
    bool call_button_;

    // Going up/down buttons
    bool up_button_;
    bool down_button_;

    // One button for each floor
    std::set<FloorNumber> destination_buttons_;

};

std::ostream &operator<<(std::ostream &os, Floor &floor);

#endif //CHISS_FLOOR_H
