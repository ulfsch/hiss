//
// main.cpp - Main for command line version of chiss
//
#include "Building.h"
#include "Configuration.h"
#include "Result.h"
#include "Passenger.h"
#include "Simulator.h"

#include <cstring>
#include <getopt.h>
#include <iostream>

static void run_simulation(Configuration &, Result &, bool verbose);

static void print_simulator(const Simulator *simulator);
static void print_usage(const char *arg);


/**
 * Constants.
 */
const Duration SIMULATION_RATE = 1;      // Seconds/simulation_step

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
        }
    }

    if (optind == argc)
    {
        print_usage(argv[0]);
    }

    Configuration configuration;
    bool ok = true;
    for (int i = optind; i < argc && ok; i++)
    {
        ok = configuration.parse_from_xml(argv[i]);
        if (!ok)
        {
            printf("Can't parse configuration file %s\n", argv[i]);
        }
    }

    if (ok)
    {
        Result result;
        run_simulation(configuration, result, opt_verbose);
        std::cout << result << std::endl;
    }

    return ok ? 0  : 1;
}

/**
 * Run a simulation.
 *
 * @param configuration
 * @param result
 * @param verbose
 */
static void run_simulation(Configuration &configuration, Result &result, bool verbose)
{
    Simulator simulator(configuration.traffic(), configuration.algorithm(), configuration.building());

    Time simulation_time = 0;
    while (!simulator.done())
    {
        simulator.simulation_step(simulation_time, simulation_time);
        simulation_time += SIMULATION_RATE;
        if (verbose)
        {
            print_simulator(&simulator);
        }
    }

    result.compute_result(simulation_time, simulator.passengers());
}

/**
 * Print a building with passengers.
 *
 * @param building
 * @param passengers
 */
static void print_simulator(const Simulator *simulator)
{
    const Building *building = simulator->building();
    const PassengerList &passengers = simulator->passengers();

    printf("%-30s", "Floor");

    for (Car *e: simulator->cars())
    {
        (void)e;
        printf("%-30s", "Elevator");
    }
    printf("\n");

    for (auto row = building->floors().rbegin(); row != building->floors().rend(); ++row)
    {
        int row_number = (*row)->number();
        int elevator_id = 0;
        int column = 0;

        column += printf("%2d: ", row_number);

        for (const auto passenger : passengers)
        {
            if (passenger->on_start_floor() && passenger->begin_floor() == (*row)->number())
            {
                column += passenger->print();
            }
        }

        for (Car *car : simulator->cars())
        {
            elevator_id += 1;
            while (column < 30 * elevator_id)
            {
                column += printf(" ");
            }
            column += printf("%2d: ", row_number);

            if (car->current_floor() == row_number)
            {
                column += printf("e[to %d ", car->next_floor());
                for (const auto passenger : passengers)
                {
                    if (passenger->car() == car)
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
 * @param arg program name
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
    fprintf(stderr, "Usage: %s [OPTIONS] <config_files>\n", program);
    fprintf(stderr, " Elevator simulator\n\n");
    fprintf(stderr, " config_files: Configuration xml files\n");
    fprintf(stderr, " OPTIONS: \n");
    fprintf(stderr, "  -v: verbose\n");

    exit(2);
}

// End of file
