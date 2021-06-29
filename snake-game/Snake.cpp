#include "Snake.h"

#include "constants.h"

Snake::Snake() {
    this->length = this->DEFAULT_LENGTH;
    this->head_position = Point(5, 5);
    this->direction = this->DEFAULT_DIRECTION;
    this->field_size = 0;
}

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
