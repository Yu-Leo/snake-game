#include "GameField.h"

#include <algorithm>

#include "Apple.h"
#include "Snake.h"

GameField::GameField() {
    this->init_field();
    this->apple = Apple(this->get_random_empty_cell());
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
    Point hp = snake.get_head_pos();
    if (field[hp.y][hp.x] != this->FIELD_CELL_TYPE_NONE) {
        switch (field[hp.y][hp.x]) {
            case FIELD_CELL_TYPE_APPLE:
                snake.increase_length();
                this->grow_snake();
                this->apple = Apple(this->get_random_empty_cell());
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

bool GameField::is_cell_empty(const Point& cell) {
    return this->field[cell.x][cell.y] == this->FIELD_CELL_TYPE_NONE;
}

int GameField::count_empty_cells() {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            count += int(this->is_cell_empty(Point(j, i)));
        }
    }
    return count;
}

Point GameField::get_random_empty_cell() {
    int empty_cells = this->count_empty_cells();
    int target_empty_cell_index = rand() % empty_cells;
    int empty_cell_index = 0;
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (field[i][j] == FIELD_CELL_TYPE_NONE) {
                if (empty_cell_index == target_empty_cell_index) {
                    return Point(j, i);
                }
                empty_cell_index++;
            }
        }
    }
    throw std::exception("No empty cells");
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