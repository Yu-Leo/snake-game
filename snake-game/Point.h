#pragma once

#include <iostream>

struct Point {
    int x = 0;
    int y = 0;

    Point(int x, int y);

    Point() : Point(0, 0) {};

    bool operator==(const Point& other);
};

std::ostream& operator<<(std::ostream& out, const Point& point);
