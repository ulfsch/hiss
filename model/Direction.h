//
// Direction.h.
//

#ifndef CHISS_DIRECTION_H
#define CHISS_DIRECTION_H

enum class Direction {
    NONE, UP, DOWN
};

bool operator==(Direction a, Direction b);
bool operator!=(Direction a, Direction b);

#endif //CHISS_DIRECTION_H
