//
// Building.h
//
#ifndef CHISS_BUILDING_H
#define CHISS_BUILDING_H

#include "Elevator.h"
#include "Floor.h"
#include <list>
#include <vector>
#include <QtCore>


/**
 * Building is group of elevators and floors.
 */
class Building : public QObject
{
Q_OBJECT

public:
    explicit Building(FloorNumber number_of_floors);

    void add_elevator(Elevator *elevator);

    void add_floor(Floor *floor);

    std::vector<Elevator *> &elevators()
    { return elevators_; }

    std::vector<Floor *> &floors()
    { return floors_; }

    virtual ~Building();

private:
    std::vector<Elevator *> elevators_;
    std::vector<Floor *> floors_;

};

std::ostream &operator<<(std::ostream &os, Building &);

#endif //CHISS_BUILDING_H
