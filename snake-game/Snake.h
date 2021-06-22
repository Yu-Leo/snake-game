#pragma once

#include <vector>

#include "Point.h"
#include "constants.h"

class Snake {
public:

    Snake();

    Point get_point_by_index(int index); // Get point by it's index in dots list
       
    int get_size();

    void move();

    void change_direction(int new_direction);

    bool check_collision_with_body(); // It's snake eating itself

    void increase_size();

    std::vector<Point> get_points();

private:
    static const int DEFAULT_SIZE = 3;

    Point dots[GAME_FIELD_SIZE * GAME_FIELD_SIZE];
    int size;
    int direction;

    void init_snake_dots(); // Init snake in starts coordinates

    bool is_change_of_direction_correct(int new_direction);
};

