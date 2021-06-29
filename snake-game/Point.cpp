#include "Point.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point& other) {
    return this->x == other.x && this->y == other.y;
}

std::ostream& operator<< (std::ostream& out, const Point& point) {
    out << '(' << point.x << ", " << point.y << ')';
    return out;
}