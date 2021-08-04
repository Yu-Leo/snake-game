#pragma once

#include "Point.h"

class Apple {
public:

    Apple();

    Apple(const Point& point); // Init apple in point coordinates

    Point get_coordinates();

protected:

    Point coordinates;
};