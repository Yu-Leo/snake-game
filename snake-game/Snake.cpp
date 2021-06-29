#include "Snake.h"

#include "constants.h"

Snake::Snake() {
    this->length = this->DEFAULT_LENGTH;
    this->head_position = Point(5, 5);
    this->direction = this->DEFAULT_DIRECTION;
    /*
    this->init_snake_dots();
    this->size = this->DEFAULT_SIZE;
    
    */
}

/*
Point Snake::get_point_by_index(int index) { // Get point by it's index in dots list
    if (index >= this->size) {
        std::cout << "error\n";
        return Point(999, 999);
    }
    return this->dots[index];
}

int Snake::get_size() {
    return this->size;
}
*/
void Snake::move_head() {
    switch (this->direction) {
        case Directions::RIGHT:
            this->head_position.x++;
            if (this->head_position.x >= this->field_size)
                this->head_position.x = 0;
            break;
        case Directions::DOWN:
            this->head_position.y++;
            if (this->head_position.y >= this->field_size)
                this->head_position.y = 0;
            break;
        case Directions::LEFT:
            this->head_position.x--;
            if (this->head_position.x < 0)
                this->head_position.x = this->field_size - 1;
            break;
        case Directions::UP:
            this->head_position.y--;
            if (this->head_position.y < 0)
                this->head_position.y = this->field_size - 1;
            break;
        default:
            break;
    }
}

/*
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
    dots.push_back(dots.back());
}

std::vector<Point> Snake::get_points() {
    return this->dots;
}

void Snake::init_snake_dots() { // Init snake horizontal in top left corner
    for (int i = 0; i < this->DEFAULT_SIZE; i++) {
        dots.push_back(Point(this->DEFAULT_SIZE - i - 1, 0));
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
*/