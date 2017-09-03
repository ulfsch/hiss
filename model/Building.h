//
// Building.h
//
#ifndef CHISS_BUILDING_H
#define CHISS_BUILDING_H


#include "Elevator.h"
#include "Floor.h"
#include <list>

class Building {
public:
    std::list<Elevator>& elevators() { return elevators_; }
    std::list<Floor>& floors() { return floors_; }

private:
    std::list<Elevator> elevators_;
    std::list<Floor> floors_;

};

std::ostream& operator<<(std::ostream& os, Building&);

#endif //CHISS_BUILDING_H
