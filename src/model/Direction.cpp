//
// Direction.cpp.
//

#include "Direction.h"

bool operator==(Direction a, Direction b)
{
    int ai = static_cast<int>(a);
    int bi = static_cast<int>(b);
    return (ai == 1 && bi == 1) ||
           (ai == 2 && bi == 2) ||
           (ai == 3 && bi == 3) ||
           (ai == 0 && bi == 1) ||
           (ai == 0 && bi == 2) ||
           (ai == 1 && bi == 0) ||
           (ai == 2 && bi == 0);
}

// End of file
