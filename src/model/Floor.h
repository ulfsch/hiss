//
// Floor.h.
//
#ifndef CHISS_FLOOR_H
#define CHISS_FLOOR_H

#include "common.h"
#include <set>
#include <QtCore>

class Floor : public QObject
{
Q_OBJECT

public:
    explicit Floor(FloorNumber floor_number, QObject *parent = nullptr);

    FloorNumber number() const { return number_; }

    bool call_button() const { return call_button_; }
    bool down_button() const { return down_button_; }
    bool up_button() const { return up_button_; }

    void press_buttons(FloorNumber destination_floor);
    void clear_buttons();

private:
    FloorNumber number_;

    // Single call button
    bool call_button_;

    // Going up/down destination_buttons
    bool up_button_;
    bool down_button_;

    // One button for each floor
    std::set<FloorNumber> floor_buttons_;
};

std::ostream &operator<<(std::ostream &os, const Floor &floor);

#endif //CHISS_FLOOR_H
