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
Elevator::Elevator(FloorNumber min_floor, FloorNumber max_floor, QObject *parent /*, int velocity, int floor_height */)
        :
        QObject(parent),
        min_floor_(min_floor),
        max_floor_(max_floor)
// car_(min_floor, velocity, floor_height)
{
    for (FloorNumber i = min_floor; i < max_floor; i++)
    {
        floors_.insert(i);
    }
}

/**
 * Constructor.
 *
 * @param floor_array array of floor numbers
 * @param len length of array
 * @param velocity  elevator speed in m/s
 * @param floor_height in meter
 */
Elevator::Elevator(FloorNumber *floor_array, size_t len, QObject *parent /*, int velocity, int floor_height */) :
        QObject(parent),
        min_floor_(0),
        max_floor_(0),
        // car_(floor_array[0], velocity, floor_height),
        floors_(floor_array, floor_array + len)
{
    if (len > 0)
    {
        max_floor_ = *std::max_element(floors_.begin(), floors_.end());
    }
}

// End of file
