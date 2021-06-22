#include "Apple.h"

#include "constants.h"
#include "Point.h"

Apple::Apple() {}

Apple::Apple(const Point& point) {
    this->coordinates = point;
}

Point Apple::get_coordinates() {
    return this->coordinates;
}