#include "RandomPoint.h"

#include <vector>

#include "constants.h"

RandomPoint::RandomPoint() {
    this->x = rand() % GAME_FIELD_SIZE;
    this->y = rand() % GAME_FIELD_SIZE;
}

RandomPoint::RandomPoint(const std::vector<Point>& acceptable_points) {
    int number_of_points = acceptable_points.size();
    int random_index = rand() % number_of_points;
    Point point = acceptable_points[random_index];
    this->x = point.x;
    this->y = point.y;
}