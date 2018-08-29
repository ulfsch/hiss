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
#include <ncurses.h>
#include <iostream>
#include <unistd.h>

static void print_building(Building &);

static void run(Simulator &, bool graph, bool verbose);

static void print_usage(const char *arg);


/**
 * Constants.
 */
const Duration SIMULATION_RATE = 1;      // Seconds/execute

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
    bool opt_graphical = false;
    int c;

    while ((c = getopt(argc, argv, "gv?")) != -1)
    {
        switch (c)
        {
            case 'g':
                opt_graphical = true;
                break;
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

        Simulator simulator(configuration);
        run(simulator, opt_graphical, opt_verbose);

        // Print the result
        Result result;
        result.compute_result(simulator.all_passengers());
        std::cout << result << std::endl;
    }
    return 0;
}

/**
 * Run the simulator.
 *
 * @param simulator
 * @param graph ncurses output
 * @param verbose
 */
static void run(Simulator &simulator, bool graph, bool verbose)
{
    Time time = 0;

    if (graph)
    {
        initscr();
        while (!simulator.done())
        {
            simulator.execute(time, SIMULATION_RATE);
            time += SIMULATION_RATE;
            print_building(simulator.building());
            sleep(1);
        }
        endwin();
    }
    else
    {
        while (!simulator.done())
        {
            simulator.execute(time, SIMULATION_RATE);
            time += SIMULATION_RATE;
            if (verbose)
            {
                std::cout << simulator.building() << std::endl;
            }
        }
    }
}

/**
 * Print on ncurses window.
 *
 * @param building
 */
static void print_building(Building &building)
{
    int row = 0;
    int column = 0;
    wclear(stdscr);

    wmove(stdscr, row, 0);
    waddch(stdscr, ACS_ULCORNER);
    whline(stdscr, ACS_HLINE, 28);
    wmove(stdscr, row, 29);
    waddch(stdscr, ACS_URCORNER);

    for (auto i = building.floors().rbegin(); i != building.floors().rend(); ++i)
    {
        wmove(stdscr, ++row, 0);
        waddch(stdscr, ACS_VLINE);

        wprintw(stdscr, "%2d: ", i->number());
        for (const auto passenger : i->passengers())
        {
            wprintw(stdscr, " p%-2d ", passenger->id());
        }

        wmove(stdscr, row, 29);
        waddch(stdscr, ACS_VLINE);
    }
    wmove(stdscr, ++row, 0);
    waddch(stdscr, ACS_LLCORNER);
    whline(stdscr, ACS_HLINE, 28);
    wmove(stdscr, row, 29);
    waddch(stdscr, ACS_LRCORNER);

    column = 30;
    for (Elevator &elevator : building.elevators())
    {
        row = building.floors().size() - elevator.car().current_floor();

        wmove(stdscr, row - 1, column);
        waddch(stdscr, ACS_ULCORNER);
        whline(stdscr, ACS_HLINE, 28);
        wmove(stdscr, row - 1, column + 29);
        waddch(stdscr, ACS_URCORNER);

        wmove(stdscr, row, column);
        waddch(stdscr, ACS_VLINE);
        for (const auto passenger : elevator.passengers())
        {
            wprintw(stdscr, " p%-2d ", passenger->id());
        }
        wmove(stdscr, row, column + 29);
        waddch(stdscr, ACS_VLINE);

        wmove(stdscr, row + 1, column);
        waddch(stdscr, ACS_LLCORNER);
        whline(stdscr, ACS_HLINE, 28);
        wmove(stdscr, row + 1, column + 29);
        waddch(stdscr, ACS_LRCORNER);

        column += 30;
    }

    wmove(stdscr, 0, 0);
    wrefresh(stdscr);
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
