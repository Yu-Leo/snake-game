#include "Snake.h"

Snake::Snake() {}

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

void Snake::set_field_size(int field_size) {
    this->field_size = field_size;
}

Point Snake::get_head_pos() const {
    return this->head_position;
}

int Snake::get_length() const {
    return this->length;
}

int Snake::get_direction() const {
    return this->direction;
}

void Snake::increase_length() {
    this->length++;
}

void Snake::change_direction(int new_direction) {
    this->direction = new_direction;
}