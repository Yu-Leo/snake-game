#pragma once

#include <vector>

#include "Point.h"

struct RandomPoint : public Point {

    RandomPoint(const std::vector<Point>& acceptable_points);
};

