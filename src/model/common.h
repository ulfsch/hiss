//
// common.h.
//
#ifndef CHISS_COMMON_H
#define CHISS_COMMON_H

#include <cstddef>
#include <set>

typedef unsigned int Id;
typedef unsigned int MilliSeconds;
typedef int FloorNumber;

typedef std::set<FloorNumber> NumberSet;

enum class Direction { DOWN, UP };

const MilliSeconds SIMULATION_RATE = 1000;      // MilliSeconds/tick

inline int modulo(int x, int mod)
{
    int result = x % mod;
    if (result < 0)
    {
        result += mod;
    }
    return result;
}

#endif //CHISS_COMMON_H
