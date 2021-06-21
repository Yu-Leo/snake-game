#include "Apple.h"

#include "constants.h"
#include "Point.h"

Apple::Apple() {
    coordinates = Point(this->generate_random_coord(),
        this->generate_random_coord());
}

Apple::Apple(int x, int y) {
    coordinates = Point(x, y);
}

Point Apple::get_coordinates() {
    return coordinates;
}

int Apple::generate_random_coord() {
    return rand() % (GAME_FIELD_SIZE + 1);
}