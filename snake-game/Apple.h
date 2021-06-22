#pragma once

#include "Point.h"

class Apple {
public:

    Apple();

    Apple(const Point& point);

    Point get_coordinates();

private:
    Point coordinates;
};