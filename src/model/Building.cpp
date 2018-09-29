//
// Building.cpp
//
#include "Building.h"

Building::Building(FloorNumber number_of_floors)
{
    for (FloorNumber i = 0; i < number_of_floors; i++)
    {
        floors_.push_back(new Floor(i));
    }
}

Building::~Building()
{
    for (auto *elevator : elevators_)
    {
        delete elevator;
    }
    for (auto *floor : floors_)
    {
        delete floor;
    }
}

void Building::add_elevator(Elevator *elevator)
{
    elevators_.push_back(elevator);
}

void Building::add_floor(Floor *floor)
{
    floors_.push_back(floor);
}

std::ostream &operator<<(std::ostream &os, Building &building)
{
    for (auto elevator : building.elevators())
    {
        os << elevator << std::endl;
    }
    for (auto i = building.floors().rbegin(); i != building.floors().rend(); ++i)
    {
        os << *i << std::endl;
    }
    return os;
}

// End of file
