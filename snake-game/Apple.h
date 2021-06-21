#pragma once

#include "Point.h"

class Apple {
public:
    Apple();

    Apple(int x, int y);

    Point get_coordinates();

private:
    Point coordinates;

    int generate_random_coord();
};