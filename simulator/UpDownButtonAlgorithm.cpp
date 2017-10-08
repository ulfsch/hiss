//
// UpDownButtonAlgorithm.cpp.
//

#include "UpDownButtonAlgorithm.h"
#include "../model/Building.h"
#include <algorithm>
#include <iostream>

/**
 * Algorithm for two call buttons (up/down) on each floor.
 *
 * @param building
 */
void UpDownButtonAlgorithm::operator()(Building &building) {
    for (Elevator &elevator : building.elevators()) {
        std::vector<Stop> stops;

        for (FloorNumber x : elevator.buttons()) {
            stops.push_back(Stop(x));
        }

        for (const Floor &floor : building.floors()) {
            if (floor.down_button()) {
                stops.push_back(Stop(floor.number(), Direction::DOWN));
            }
            if (floor.up_button()) {
                stops.push_back(Stop(floor.number(), Direction::UP));
            }
        }

        if (!stops.empty()) {
            Comp comp(elevator.current_floor(), elevator.direction());
            std::sort(stops.begin(), stops.end(), comp);
            elevator.go_to(stops.begin()->floor);
        }
    }
}

/**
 * The compare function.
 *
 * @param a
 * @param b
 * @return true if stop a is better than stop b given a elevator position and direction
 */
bool UpDownButtonAlgorithm::Comp::operator()(const Stop &a, const Stop &b) {
    int a_delta = a.floor - current_;
    int b_delta = b.floor - current_;
    Direction a_dir = (a_delta < 0) ? Direction::DOWN : Direction::UP;
    Direction b_dir = (b_delta < 0) ? Direction::DOWN : Direction::UP;

    // Prefer a stop in the elevator direction.
    if (a_dir == direction_ && b_dir != direction_) {
        return true;
    }
    if (a_dir != direction_ && b_dir == direction_) {
        return false;
    }

    // Prefer stop ... direction
    if (a.direction == a_dir && b.direction != b_dir) {
        return true;
    }
    if (a.direction != a_dir && b.direction == b_dir) {
        return false;
    }
//    if (a.direction != a_dir && b.direction != b_dir) {
//        return std::abs(a_delta) > std::abs(b_delta);
//    }

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
