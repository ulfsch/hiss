//
// Created by ulf on 8/20/19.
//

#include <Building.h>
#include <Elevator.h>
#include "EvalAlgorithm.h"


EvalAlgorithm::Stop::Stop(FloorNumber n, Direction d) :
        floor (n),
        direction(d),
        weight(0)
{

}

void EvalAlgorithm::operator()(Building *building)
{
    for (Elevator *elevator : building->elevators())
    {
        std::vector<Stop> stops;

        for (FloorNumber x : elevator->destination_buttons())
        {
            stops.push_back(Stop(x));
        }

        for (const Floor *floor : building->floors())
        {
            if (floor->down_button())
            {
                stops.push_back(Stop(floor->number(), Direction::DOWN));
            }
            if (floor->up_button())
            {
                stops.push_back(Stop(floor->number(), Direction::UP));
            }
        }

        if (!stops.empty())
        {
            Comp comp(elevator->current_floor(), elevator->direction());
            std::sort(stops.begin(), stops.end(), comp);
            for (auto stop : stops)
            {
                if (stop.floor != elevator->current_floor())
                {
                    elevator->set_next_floor(stop.floor);
                    break;
                }
            }
        }
        else
        {
            printf("XXX %d\n", stops.size());
        }
    }

}
