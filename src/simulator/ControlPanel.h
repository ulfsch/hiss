//
// Created by ulf on 2/9/20.
//

#ifndef CHISS_CONTROLPANEL_H
#define CHISS_CONTROLPANEL_H

#include "Car.h"
#include <Passenger.h>
#include <map>


class ControlPanel
{
public:
    void press_floor_buttons(Passenger* passenger);
    void press_car_buttons(Car* car, Passenger* passenger);

    void clear_floor_buttons(FloorNumber floor_number);
    void clear_car_buttons(Car* car, FloorNumber floor_number);

public:
    NumberSet floor_call_buttons;
    NumberSet floor_up_buttons;
    NumberSet floor_down_buttons;
    NumberSet floor_destination_buttons;

    std::map<Car*, NumberSet> car_target_buttons;

};


#endif //CHISS_CONTROLPANEL_H
