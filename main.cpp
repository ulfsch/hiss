//
// main.cpp
//
#include <iostream>
#include "model/Building.h"
#include "simulator/ConstantTraffic.h"
#include "simulator/CallButtonAlgorithm.h"
#include "simulator/Simulator.h"

const FloorNumber NUMBER_OF_FLOORS = 10;
const size_t NUMBER_OF_PASSENGERS = 100;
const double PASSENGER_PER_SECOND = 1.0;
const Duration DELTA_TIME = 1;


Time run() {
    ConstantTraffic traffic(NUMBER_OF_FLOORS, NUMBER_OF_PASSENGERS, PASSENGER_PER_SECOND);
    CallButtonAlgorithm algorithm;

    Building building;
    for (FloorNumber i = 0; i < NUMBER_OF_FLOORS; i++) {
        building.floors().push_back(Floor(i));
    }
    building.elevators().push_back(Elevator(0, NUMBER_OF_FLOORS));

    Simulator simulator(traffic, algorithm, building);

    // Run the simulator
    Time time = 0;
    for (time = 0; time < 100 || !Passenger::all_at_destination(); time += DELTA_TIME) {
        simulator.step(time, DELTA_TIME);
        std::cout << building << std::endl;
    }

    return time;
}

int main() {
    Time total_time = run();
    std::cout << "Total simulation time:  " << total_time << std::endl;
    std::cout << "Average waiting time:   " << Passenger::average_waiting_time() << std::endl;
    std::cout << "Average traveling time: " << Passenger::average_traveling_time() << std::endl;
    Passenger::delete_all();
    return 0;
}

// End of file
