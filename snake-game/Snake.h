#pragma once

#include <vector>

#include "Point.h"
#include "constants.h"

class Snake {
public:

    Snake();

    int length;
    Point head_position;
    int direction;

    int field_size;

    /*
    Point get_point_by_index(int index); // Get point by it's index in dots list
       
    int get_size();
    */

    void move_head();

    /*
    void change_direction(int new_direction);

    bool check_collision_with_body(); // It's snake eating itself

    void increase_size();

    std::vector<Point> get_points();
    */
private:
    static const int DEFAULT_LENGTH = 3;
    static const int DEFAULT_DIRECTION = Directions::RIGHT;
    /*
    std::vector<Point> dots;
    int size;
    

    void init_snake_dots(); // Init snake in starts coordinates

    bool is_change_of_direction_correct(int new_direction);
    */
};

