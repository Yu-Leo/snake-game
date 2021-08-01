#pragma once

#include "Apple.h"

class SuperApple : public Apple {
public:
	SuperApple() : Apple() {}

	SuperApple(const Point& point) : Apple(point) {}
};