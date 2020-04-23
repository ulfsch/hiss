//
// common.h.
//
#ifndef CHISS_COMMON_H
#define CHISS_COMMON_H

#include <cstddef>
#include <set>

typedef unsigned int Id;
typedef int FloorNumber;
typedef double Duration;
typedef unsigned int Time;

typedef std::set<FloorNumber> NumberSet;

enum class Direction { DOWN, UP };

#endif //CHISS_COMMON_H
