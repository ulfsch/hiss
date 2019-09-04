//
// CallButtonAlgorithm.cpp
//
#include "CallButtonAlgorithm.h"
#include "Building.h"


CallButtonAlgorithm::CallButtonAlgorithm()
{

}

void CallButtonAlgorithm::operator()(Building *building, std::vector<Stop> &result)
{
    for (Elevator *elevator : building->elevators())
    {
        if (!elevator->destination_buttons().empty())
        {
            // First check elevator destination_buttons
            elevator->set_next_floor(*elevator->destination_buttons().begin());
        }
        else
        {
            // No elevator buttons pressed. Check floor call buttons.
            for (const auto *floor : building->floors())
            {
                if (floor->call_button())
                {
                    elevator->set_next_floor(floor->number());
                }
            }
        }
    }
}

// End of file
