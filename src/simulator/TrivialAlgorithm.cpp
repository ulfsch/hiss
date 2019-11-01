//
// TrivialAlgorithm.cpp
//
#include "TrivialAlgorithm.h"
#include "Building.h"
#include "Simulator.h"


TrivialAlgorithm::TrivialAlgorithm()
{

}

void TrivialAlgorithm::operator()(Simulator *simulator, std::vector<Stop> &stops)
{
    for (Car *car : simulator->cars())
    {
        // First check elevator buttons
        for (FloorNumber floorNumber : car->destination_buttons())
        {
            stops.push_back(Stop(car, floorNumber));
        }

        // Check floor call buttons.
        for (const auto *floor : simulator->building()->floors())
        {
            if (floor->call_button())
            {
                stops.push_back(Stop(car, floor->number()));
            }
        }

    }
}

// End of file
