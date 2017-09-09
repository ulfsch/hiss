//
// Building.cpp
//
#include "Building.h"

std::ostream &operator<<(std::ostream &os, Building &building) {
    for (auto &elevator : building.elevators()) {
        os << elevator << std::endl;
    }
    for (auto i = building.floors().rbegin(); i != building.floors().rend(); ++i) {
        os << *i << std::endl;
    }
    return os;
}

// End of file
