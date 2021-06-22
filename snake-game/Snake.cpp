#include "Snake.h"

#include "constants.h"

Snake::Snake() {
    this->init_snake_dots();
    this->size = this->DEFAULT_SIZE;
    this->direction = Directions::RIGHT;
}

Point Snake::get_point_by_index(int index) { // Get point by it's index in dots list
    return this->dots[index];
}

int Snake::get_size() {
    return this->size;
}

void Snake::move() {
    for (int i = this->size; i > 0; i--) {
        this->dots[i] = this->dots[i - 1];
    }

    switch (this->direction) {
    case Directions::RIGHT:
        dots[0].x++;
        break;
    case Directions::DOWN:
        dots[0].y++;
        break;
    case Directions::LEFT:
        dots[0].x--;
        break;
    case Directions::UP:
        dots[0].y--;
        break;
    default:
        break;
    }
}

void Snake::change_direction(int new_direction) {
    if (!this->is_change_of_direction_correct(new_direction)) {
        std::cout << "error\n";
        return;
    }

    this->direction = new_direction;
}

bool Snake::check_collision_with_body() { // It's snake eating itself
    for (int i = 0; i < this->size; i++) {
        if (i > 3 && dots[i] == dots[0]) {
            return true;
        }
    }
    return false;
}

void Snake::increase_size() {
    this->size++;
}

std::vector<Point> Snake::get_points() {
    std::vector<Point> points;
    for (int i = 0; i < this->size; i++) {
        points.push_back(this->dots[i]);
    }
    return points;
}

void Snake::init_snake_dots() { // Init snake in (0, 0), (1, 0), (2, 0)
    for (int i = 0; i < this->DEFAULT_SIZE; i++) {
        dots[i] = Point(this->DEFAULT_SIZE - i - 1, 0);
    }
}

bool Snake::is_change_of_direction_correct(int new_direction) {
    bool correct_value = (
        new_direction == Directions::RIGHT ||
        new_direction == Directions::DOWN ||
        new_direction == Directions::LEFT ||
        new_direction == Directions::UP);

    // Snake can't change direction to opposit sharply
    bool check_from_left =
        (this->direction == Directions::LEFT && new_direction != Directions::RIGHT);
    bool check_from_right =
        (this->direction == Directions::RIGHT && new_direction != Directions::LEFT);
    bool check_from_up =
        (this->direction == Directions::UP && new_direction != Directions::DOWN);
    bool check_from_down =
        (this->direction == Directions::DOWN && new_direction != Directions::UP);

    return (correct_value && (check_from_left || check_from_right ||
        check_from_up || check_from_down));
}