//
// CallButtonAlgorithm.cpp.
//
#include "CallButtonAlgorithm.h"
#include "../model/Building.h"


CallButtonAlgorithm::CallButtonAlgorithm() {

}

void CallButtonAlgorithm::operator()(Building &building) {
    for (Elevator &elevator : building.elevators()) {
        if (!elevator.buttons().empty()) {

            // First check elevator buttons
            elevator.go_to(*elevator.buttons().begin());
        } else {

            // No elevator buttons pressed. Check floor buttons.
            for (const auto &floor : building.floors()) {
                if (floor.call_button()) {
                    elevator.go_to(floor.number());
                }
            }
        }
    }
}

// End of file
