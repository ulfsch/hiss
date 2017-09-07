//
// UpDownButtonAlgorithm.cpp.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include "UpDownButtonAlgorithm.h"
#include "../model/Building.h"


void UpDownButtonAlgorithm::operator()(Building &building) {
    for (Elevator &elevator : building.elevators()) {
        std::vector<Stop> stops;

        for (FloorNumber x : elevator.buttons()) {
            stops.push_back(Stop(x));
        }

        for (const Floor &floor : building.floors()) {
            if (floor.down_button()) {
                stops.push_back(Stop(floor.number(), Direction::DOWN));
            } else if (floor.up_button()) {
                stops.push_back(Stop(floor.number(), Direction::UP));
            }
        }

        if (!stops.empty()) {
            Comp comp(elevator.current_floor(), elevator.direction());
            std::sort(stops.begin(), stops.end(), comp);
            elevator.go_to(stops.begin()->floor);
        }

//        for (Stop s : stops) {
//            std::cout << s;
//        }
//        std::cout << std::endl;
    }
}

bool UpDownButtonAlgorithm::Comp::operator()(const Stop &a, const Stop &b) {
    int a_delta = a.floor - current_;
    int b_delta = b.floor - current_;

    bool a_same_dir = a.direction == direction_ || a.direction == Direction::NONE || direction_ == Direction::NONE;
    bool b_same_dir = b.direction == direction_ || b.direction == Direction::NONE || direction_ == Direction::NONE;

    // Change of direction is always bad
    if (a_delta > 0 && b_delta < 0 && direction_ == Direction::UP) {
        return true;
    }
    if (a_delta < 0 && b_delta > 0 && direction_ == Direction::DOWN) {
        return true;
    }
    if (a_delta < 0 && b_delta > 0 && direction_ == Direction::UP) {
        return false;
    }
    if (a_delta > 0 && b_delta < 0 && direction_ == Direction::DOWN) {
        return false;
    }

    // Prefer passengers in the elevator direction
    if (a_same_dir && !b_same_dir) {
        return true;
    }
    if (!a_same_dir && b_same_dir) {
        return false;
    }

    // Shortest distance
    return std::abs(a_delta) < std::abs(b_delta);
}

std::ostream &operator<<(std::ostream &os, UpDownButtonAlgorithm::Stop &s) {
    if (s.direction == Direction::UP)
        os << std::string(" ") << s.floor << "u";
    if (s.direction == Direction::DOWN)
        os << std::string(" ") << s.floor << "d";
    if (s.direction == Direction::NONE)
        os << std::string(" ") << s.floor << "-";
    return os;
}

// End of file
