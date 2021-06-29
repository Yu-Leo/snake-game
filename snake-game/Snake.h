#pragma once

#include <vector>

#include "Point.h"
#include "constants.h"

class Snake {
public:
    int length;
    Point head_position;
    int direction;
    int field_size;

    Snake();

    void move_head();

private:
    static const int DEFAULT_LENGTH = 3;
    static const int DEFAULT_DIRECTION = Directions::RIGHT;
};

