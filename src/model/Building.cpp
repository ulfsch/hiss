//
// Building.cpp
//
#include "Building.h"

Building::Building(FloorNumber number_of_floors, QObject *parent) :
        QObject(parent),
        number_of_floors_(number_of_floors)
{
    for (FloorNumber i = 0; i < number_of_floors; i++)
    {
        floors_.push_back(new Floor(i, this));
    }
}

void Building::add_elevator(Elevator *elevator)
{
    if (elevator->max_floor() <= number_of_floors_)
    {
        elevators_.push_back(elevator);
        emit changed();
    }
}

void Building::add_floor(Floor *floor)
{
    floors_.push_back(floor);
    emit changed();
}

FloorNumber Building::getNumber_of_floors() const
{
    return number_of_floors_;
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
