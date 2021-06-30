#include "GameField.h"

#include <algorithm>

#include "Apple.h"
#include "Snake.h"

GameField::GameField() {
    this->init_field();

    int dot = this->get_random_empty_cell();
    this->apple = Apple(Point(dot % this->size, dot / this->size));
    this->snake.set_field_size(this->size);
    this->render_snake();
    this->render_apple();
}

void GameField::move_snake() {
    this->snake.move_head();
    this->check_collisions();
    Point hp = snake.get_head_pos();
    field[hp.y][hp.x] = snake.get_length() + 1;
    this->decrease_snake_cells();
}

void GameField::turn_snake(int direction) {
    this->snake.change_direction(direction);
}

int GameField::get_snake_direction() const {
    return this->snake.get_direction();
}

void GameField::check_collisions() {
    int dot;
    Point hp = snake.get_head_pos();
    if (field[hp.y][hp.x] != this->FIELD_CELL_TYPE_NONE) {
        switch (field[hp.y][hp.x]) {
            
            case FIELD_CELL_TYPE_APPLE:
                snake.increase_length();
                this->grow_snake();
                dot = this->get_random_empty_cell();
                this->apple = Apple(Point(dot % this->size, dot / this->size));
                this->render_apple();
                break;
            default:
                throw 1;
                break;
        }
    }
}

void GameField::grow_snake() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (field[i][j] > FIELD_CELL_TYPE_NONE) {
                field[i][j]++;
            }
        }
    }
}

void GameField::decrease_snake_cells() {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (this->field[i][j] > this->FIELD_CELL_TYPE_NONE) {
                this->field[i][j]--;
            }
        }
    }
}

void GameField::resize_matrix() {
    this->field.resize(this->size);
    for (int i = 0; i < this->size; i++) {
        this->field[i].resize(this->size);
    }
}

void GameField::init_field() { // Fill the matrix with FIELD_CELL_TYPE_NONE
    this->resize_matrix();

    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            this->field[i][j] = this->FIELD_CELL_TYPE_NONE;
        }
    }
}

void GameField::render_snake() {
    int snake_len = snake.get_length();
    for (int i = 0; i < snake_len; i++) {
        Point hp = snake.get_head_pos();
        field[hp.y][hp.x - i] = snake_len - i;
    }
}

void GameField::render_apple() {
    Point dot = this->apple.get_coordinates();
    this->field[dot.y][dot.x] = this->FIELD_CELL_TYPE_APPLE;
}

int GameField::get_random_empty_cell() {
    int empty_cell_count = 0;
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (this->field[i][j] == this->FIELD_CELL_TYPE_NONE)
                empty_cell_count++;
        }
    }

    int target_empty_cell_index = rand() % empty_cell_count;

    int empty_cell_index = 0;
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (field[i][j] == FIELD_CELL_TYPE_NONE) {
                if (empty_cell_index == target_empty_cell_index) {
                    return i * this->size + j;
                }
                empty_cell_index++;
            }
        }
    }
    return -1;
}

std::ostream& operator<< (std::ostream& out, const GameField& game_field) {
    for (int i = 0; i < game_field.size; i++) {
        for (int j = 0; j < game_field.size; j++) {
            switch (game_field.field[i][j]) {
                case game_field.FIELD_CELL_TYPE_NONE:
                    out << (char)GameField::Symbols::NONE;
                    break;
                case game_field.FIELD_CELL_TYPE_APPLE:
                    out << (char)GameField::Symbols::APPLE;
                    break;
                default:
                    out << (char)GameField::Symbols::SNAKE;
                    break;
            }
            out << ' ';
        }
        out << '\n';
    }
    return out;
}