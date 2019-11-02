//
// Elevator.cpp
//

#include "Elevator.h"


/**
 * Constructor.
 * 
 * @param min_floor lowest floor number. Bottom floor is 0
 * @param max_floor highest floor number + 1
 * @param velocity  elevator speed in m/s
 * @param floor_height in meter
 */
Elevator::Elevator(FloorNumber min_floor, FloorNumber max_floor, QObject *parent) :
        QObject(parent),
        min_floor_(min_floor),
        max_floor_(max_floor)
{
    for (FloorNumber floor_number = min_floor; floor_number < max_floor; floor_number++)
    {
        floors_.insert(floor_number);
    }
}

/**
 * Constructor.
 *
 * @param floor_array array of floor numbers
 * @param len length of array
 */
Elevator::Elevator(FloorNumber *floor_array, size_t len, QObject *parent) :
        QObject(parent),
        min_floor_(0),
        max_floor_(0),
        floors_(floor_array, floor_array + len)
{
    if (len > 0)
    {
        max_floor_ = *std::max_element(floors_.begin(), floors_.end());
        min_floor_ = *std::min_element(floors_.begin(), floors_.end());
    }
}

// End of file
