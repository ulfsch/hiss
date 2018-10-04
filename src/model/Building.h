//
// Building.h
//
#ifndef CHISS_BUILDING_H
#define CHISS_BUILDING_H

#include "Elevator.h"
#include "Floor.h"
#include <vector>
#include <QtCore>


/**
 * Building is group of elevators and floors.
 */
class Building : public QObject
{
Q_OBJECT

public:
    explicit Building(FloorNumber number_of_floors, QObject *parent);

    void add_elevator(Elevator *elevator);
    void add_floor(Floor *floor);

    FloorNumber getNumber_of_floors() const;

    std::vector<Elevator *> &elevators()
    { return elevators_; }

    std::vector<Floor *> &floors()
    { return floors_; }

signals:

    void changed();

private:
    FloorNumber number_of_floors_;

private:
    std::vector<Elevator *> elevators_;
    std::vector<Floor *> floors_;

};

std::ostream &operator<<(std::ostream &os, Building &);

#endif //CHISS_BUILDING_H
