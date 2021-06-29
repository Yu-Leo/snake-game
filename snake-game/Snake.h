#pragma once

#include <vector>

#include "Point.h"
#include "constants.h"

class Snake {
public:
    Snake();

    void move_head();

    void set_field_size(int field_size);

    Point get_head_pos() const;

    int get_length() const;

    void increase_length();

    void change_direction(int new_direction);

private:
    static const int DEFAULT_LENGTH = 3;
    static const int DEFAULT_DIRECTION = Directions::RIGHT;

    int length;
    Point head_position;
    int direction;
    int field_size;
};

