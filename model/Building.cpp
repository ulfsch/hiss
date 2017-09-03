//
// Building.cpp.
//

#include <algorithm>
#include "Building.h"

std::ostream &operator<<(std::ostream &os, Building &building) {
    for (auto i = building.floors().rbegin(); i != building.floors().rend(); ++i) {
        os << *i << std::endl;
    }
    for (auto i = building.elevators().begin(); i != building.elevators().end(); ++i) {
        os << *i << std::endl;
    }
    return os;
}
