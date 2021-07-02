#pragma once

#include <vector>

#include "Point.h"
#include "Size.h"

class Snake {
public:

    enum Directions { // Directions of snake's movement
        RIGHT,
        DOWN,
        LEFT,
        UP
    };

    Snake();

    void move_head();

    void set_field_size(Size field_size); // Init field size

    Point get_head_pos() const;

    int get_length() const;

    int get_direction() const;

    void increase_length(); // Increase snake length by one cell

    void change_direction(int new_direction);

private:

    int length = 3;
    Point head_position = Point(this->length - 1, 0);
    int direction = Directions::RIGHT;

    // Size of fields on which it is used snake. Needs initialization real value!
    Size field_size;
};

