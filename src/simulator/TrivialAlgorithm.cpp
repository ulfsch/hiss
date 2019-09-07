//
// TrivialAlgorithm.cpp
//
#include "TrivialAlgorithm.h"
#include "Building.h"


TrivialAlgorithm::TrivialAlgorithm()
{

}

void TrivialAlgorithm::operator()(Building *building, std::vector<Stop> &stops)
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
                    stops.push_back(Stop(elevator, floor->number()));
                }
            }
        }
    }
}

// End of file
