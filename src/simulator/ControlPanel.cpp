//
// Created by ulf on 2/9/20.
//

#include "ControlPanel.h"

void ControlPanel::press_floor_buttons(Passenger *passenger)
{
    floor_call_buttons.insert(passenger->begin_floor());

    if (passenger->end_floor() > passenger->begin_floor())
    {
        floor_up_buttons.insert(passenger->begin_floor());
    }

    if (passenger->end_floor() < passenger->begin_floor())
    {
        floor_down_buttons.insert(passenger->begin_floor());
    }

    floor_destination_buttons.insert(passenger->end_floor());
}

void ControlPanel::press_car_buttons(Car* car, Passenger *passenger)
{
    NumberSet& buttons = car_target_buttons[car];
    buttons.insert(passenger->end_floor());
}

void ControlPanel::clear_floor_buttons(FloorNumber floor_number)
{
    floor_call_buttons.erase(floor_number);
    floor_up_buttons.erase(floor_number);
    floor_down_buttons.erase(floor_number);
}

void ControlPanel::clear_car_buttons(Car *car, FloorNumber floor_number)
{
    car_target_buttons[car].erase(floor_number);
}

