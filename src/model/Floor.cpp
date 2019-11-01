//
// Floor.cpp
//
#include "Floor.h"

Floor::Floor(FloorNumber floor_number, QObject *parent) :
        QObject(parent),
        number_(floor_number),
        call_button_(false),
        up_button_(false),
        down_button_(false)
{
}

void Floor::press_buttons(FloorNumber destination_floor)
{
    call_button_ = true;

    if (destination_floor > number_)
    {
        up_button_ = true;
    }
    if (destination_floor < number_)
    {
        down_button_ = true;
    }
}

void Floor::clear_buttons()
{
    call_button_ = false;
    up_button_ = false;
    down_button_ = false;
}


// End of file
