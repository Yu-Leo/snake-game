#pragma once

#include <iostream>

struct Point {
    int x = 0;
    int y = 0;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point() : Point(0, 0) {};

    bool operator==(const Point& other) {
        return this->x == other.x && this->y == other.y;
    }

};