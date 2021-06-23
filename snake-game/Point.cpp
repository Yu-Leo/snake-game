#include "Point.h"

Point::Point() {}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point& other) {
    return this->x == other.x && this->y == other.y;
}

bool Point::operator<(const Point& other) {
    return (this->y < other.y) || (this->y == other.y && this->x < other.x);
}

std::ostream& operator<< (std::ostream& out, const Point& point) {
    out << '(' << point.x << ", " << point.y << ')';
    return out;
}