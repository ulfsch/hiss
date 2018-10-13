//
// CallButtonAlgorithm.cpp
//
#include "CallButtonAlgorithm.h"
#include "Building.h"


CallButtonAlgorithm::CallButtonAlgorithm()
{

}

void CallButtonAlgorithm::operator()(Building *building)
{
    for (Elevator *elevator : building->elevators())
    {
        if (!elevator->destination_buttons().empty())
        {

            // First check elevator destination_buttons
            elevator->car().set_next_floor(*elevator->destination_buttons().begin());
        }
        else
        {

            // No elevator buttons pressed. Check floor destination_buttons.
            for (const auto *floor : building->floors())
            {
                if (floor->call_button())
                {
                    elevator->car().set_next_floor(floor->number());
                }
            }
        }
    }
}

// End of file
