#pragma once

#include <iostream>

struct Point {
    int x = 0;
    int y = 0;

    Point();

    Point(int x, int y);

    bool operator==(const Point& other);

    bool operator<(const Point& other);
};

std::ostream& operator<< (std::ostream& out, const Point& point);
