#include "GameField.h"

GameField::GameField() {
    this->init_field();

    this->snake.set_field_size(this->size);
    this->render_snake();

    this->apple = Apple(this->get_random_empty_cell());
    this->render_apple();
}

void GameField::move_snake() {
    this->snake.move_head();
    this->check_collisions();
    Point hp = this->snake.get_head_pos();
    this->field[hp.y][hp.x] = this->snake.get_length() + 1;
    this->decrease_snake_cells();
}

void GameField::turn_snake(int direction) {
    this->snake.change_direction(direction);
}

int GameField::get_snake_direction() const {
    return this->snake.get_direction();
}

Size GameField::get_size() const{
    return this->size;
}

void GameField::resize_matrix() {
    this->field.resize(this->size.height);
    for (int i = 0; i < this->size.height; i++) {
        this->field[i].resize(this->size.width);
    }
}

void GameField::init_field() {
    this->resize_matrix();

    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            this->field[i][j] = this->FIELD_CELL_TYPE_NONE;
        }
    }
}

void GameField::check_collisions() {
    Point hp = this->snake.get_head_pos();
    if (this->field[hp.y][hp.x] != this->FIELD_CELL_TYPE_NONE) {
        switch (this->field[hp.y][hp.x]) {
            case FIELD_CELL_TYPE_APPLE:
                this->snake.increase_length();
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
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] > FIELD_CELL_TYPE_NONE) {
                this->field[i][j]++;
            }
        }
    }
}

void GameField::decrease_snake_cells() {
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] > this->FIELD_CELL_TYPE_NONE) {
                this->field[i][j]--;
            }
        }
    }
}

void GameField::render_snake() {
    int snake_len = this->snake.get_length();
    for (int i = 0; i < snake_len; i++) {
        Point hp = this->snake.get_head_pos();
        this->field[hp.y][hp.x - i] = snake_len - i;
    }
}

void GameField::render_apple() {
    Point dot = this->apple.get_coordinates();
    this->field[dot.y][dot.x] = this->FIELD_CELL_TYPE_APPLE;
}

bool GameField::is_cell_empty(const Point& cell) {
    return this->field[cell.y][cell.x] == this->FIELD_CELL_TYPE_NONE;
}

int GameField::count_empty_cells() {
    int count = 0;
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            count += int(this->is_cell_empty(Point(j, i)));
        }
    }
    return count;
}

Point GameField::get_random_empty_cell() {
    int empty_cells = this->count_empty_cells();
    int target_empty_cell_index = rand() % empty_cells;
    int empty_cell_index = 0;
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] == FIELD_CELL_TYPE_NONE) {
                if (empty_cell_index == target_empty_cell_index) {
                    return Point(j, i);
                }
                empty_cell_index++;
            }
        }
    }
    throw std::exception("No empty cells");
}

void print_cell(std::ostream& out, const GameField& game_field, const Point &cell) {
    switch (game_field.field[cell.y][cell.x]) {
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
}

std::ostream& operator<<(std::ostream& out, const GameField& game_field) {
    for (int i = 0; i < game_field.size.height; i++) {
        for (int j = 0; j < game_field.size.width; j++) {
            print_cell(out, game_field, Point(j, i));
            out << ' ';
        }
        out << '\n';
    }
    return out;
}