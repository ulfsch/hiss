//
// main.cpp
//
#include "Building.h"
#include "CallButtonAlgorithm.h"
#include "Configuration.h"
#include "ConstantTraffic.h"
#include "Result.h"
#include "Simulator.h"
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <unistd.h>

static void run_simulation(Configuration &, Result &, bool verbose);

static void print_building(const Building *building, const PassengerList &passengers);

static void print_usage(const char *arg);


/**
 * Constants.
 */
const Duration SIMULATION_RATE = 1;      // Seconds/tick

/**
 * Main program.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    bool opt_verbose = false;
    int c;

    while ((c = getopt(argc, argv, "v?")) != -1)
    {
        switch (c)
        {
            case 'v':
                opt_verbose = true;
                break;
            default:
                print_usage(argv[0]);
                exit(2);
        }
    }

    if (optind == argc)
    {
        print_usage(argv[0]);
    }
    else
    {
        Configuration configuration;
        for (int index = optind; index < argc; index++)
        {
            configuration.parse_from_xml(argv[index]);
        }

        Result result;
        run_simulation(configuration, result, opt_verbose);
        std::cout << result << std::endl;
    }
    return 0;
}

/**
 * Run the simulator.
 *
 * @param simulator
 * @param verbose
 */
static void run_simulation(Configuration &configuration, Result &result, bool verbose)
{
    Simulator simulator(configuration.traffic(), configuration.algorithm(), configuration.building());
    Time time = 0;

    while (!simulator.done())
    {
        simulator.tick(time, SIMULATION_RATE);
        time += SIMULATION_RATE;
        if (verbose)
        {
            print_building(simulator.building(), simulator.passengers());
        }
    }

    result.compute_result(time, simulator.passengers());
}

/**
 * Print .
 *
 * @param building
 */
static void print_building(const Building *building, const PassengerList &passengers)
{
    printf("No:%-27s", "Floor");
    for (Elevator *elevator : building->elevators())
    {
        printf("No:%-27s", "Elevator");
    }
    printf("\n");

    for (auto iterator = building->floors().rbegin(); iterator != building->floors().rend(); ++iterator)
    {
        int row = (*iterator)->number();
        int elevator_id = 0;
        int column = 0;

        column += printf("%2d: ", row);

        for (const auto passenger : passengers)
        {
            if (passenger->on_start_floor() && passenger->begin_floor() == *iterator)
            {
                column += passenger->print();
            }
        }

        for (Elevator *elevator : building->elevators())
        {
            elevator_id += 1;
            while (column < 30 * elevator_id)
            {
                column += printf(" ");
            }
            column += printf("%2d: ", row);

            if (elevator->current_floor() == row)
            {
                column += printf("[%d->%d ", elevator->current_floor(), elevator->next_floor());
                for (const auto passenger : passengers)
                {
                    if (passenger->elevator() == elevator)
                    {
                        column += passenger->print();
                    }
                }
                column += printf("]");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Print program help text and exit.
 *
 * @param arg
 */
static void print_usage(const char *arg)
{
    const char *program = strrchr(arg, '/');
    if (program)
    {
        program += 1;
    }
    else
    {
        program = arg;
    }
    fprintf(stderr, "Usage: %s [OPTIONS]... CONFIG...\n", program);
    fprintf(stderr, " Elevator simulator\n\n");
    fprintf(stderr, " CONFIG: Configuration xml file\n");
    fprintf(stderr, " OPTIONS: \n");
    fprintf(stderr, "  -g: graphical\n");
    fprintf(stderr, "  -v: verbose\n");

    exit(2);
}

// End of file
