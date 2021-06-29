#include "GameField.h"

#include <algorithm>

#include "Apple.h"
#include "Snake.h"
#include "RandomPoint.h"

GameField::GameField() {
    this->init_field();

    int dot = this->get_random_empty_cell();
    this->apple = Apple(Point(dot % this->size, dot / this->size));
    this->snake.field_size = this->size;
    this->render_snake();
    this->render_apple();
}
/*
void GameField::update() {
    this->init_field(); // Clear matrix
    this->render_apple();
    this->render_snake();
}
*/
void GameField::move_snake() {
    this->snake.move_head();
    this->check_collisions();
    field[snake.head_position.y][snake.head_position.x] = snake.length + 1;
    this->decrease_snake_cells();
}

void GameField::check_collisions() {
    if (field[snake.head_position.y][snake.head_position.x] != this->FIELD_CELL_TYPE_NONE) {
        switch (field[snake.head_position.y][snake.head_position.x]) {
            
            case FIELD_CELL_TYPE_APPLE:
                snake.length++;
                this->grow_snake();
                int dot = this->get_random_empty_cell();
                this->apple = Apple(Point(dot % this->size, dot / this->size));
                this->render_apple();
                break;
            /*
            default:
                game_over = true;
                break;
            */
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

/*
void GameField::check_collision_with_apple() {
    if (this->snake.get_point_by_index(0) == this->apple.get_coordinates()) {
        this->snake.increase_size();

        RandomPoint rp(this->generate_acceptable_points_for_new_apple());
        this->apple = Apple(rp);
    }
}

bool GameField::is_game_over() {
    return this->is_collision_with_snake_body() ||
        this->is_collision_with_borders();
}
*/
void GameField::turn_snake(int direction) {
    this->snake.direction = direction;
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
/*
bool GameField::is_collision_with_apple() {
    return this->snake.get_point_by_index(0) == this->apple.get_coordinates();
}

bool GameField::is_collision_with_snake_body() {
    return this->snake.check_collision_with_body();
}

bool GameField::is_collision_with_borders() {
    Point head = this->snake.get_point_by_index(0);
    return (head.x < 0 || head.x >= this->size ||
        head.y < 0 || head.y >= this->size);
}
*/
void GameField::render_snake() {
    /*
    std::vector<Point> snake_points = this->snake.get_points();
    for (Point point : snake_points) {
        this->field[point.y][point.x] = this->SNAKE_SYMBOL;
    }
    */ 
    for (int i = 0; i < snake.length; i++) {
        field[snake.head_position.y][snake.head_position.x - i] = snake.length - i;
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

/*
std::vector<Point> GameField::generate_acceptable_points_for_new_apple() {
    std::vector<Point> unacceptable_points = this->snake.get_points();

    unacceptable_points.push_back(Point(0, -1));
    unacceptable_points.push_back(Point(this->size - 1, this->size));

    std::sort(unacceptable_points.begin(), unacceptable_points.end());

    std::vector<Point> acceptable_points;
    for (int i = 0; i < unacceptable_points.size() - 1; i++) {
        int start_num = unacceptable_points[i].y * this->size +
            unacceptable_points[i].x;
        int finish_num = unacceptable_points[i + 1].y * this->size +
            unacceptable_points[i + 1].x;

        for (int num = start_num; num < finish_num; num++) {
            acceptable_points.push_back(Point(num % this->size, num / this->size));
        }
    }
    return acceptable_points;
}
*/

std::ostream& operator<< (std::ostream& out, const GameField& game_field) {
    for (int i = 0; i < game_field.size; i++) {
        for (int j = 0; j < game_field.size; j++) {
            switch (game_field.field[i][j]) {
                case game_field.FIELD_CELL_TYPE_NONE:
                    out << game_field.VOID_SYMBOL;
                    break;
                case game_field.FIELD_CELL_TYPE_APPLE:
                    out << game_field.APPLE_SYMBOL;
                    break;
                default:
                    out << game_field.field[i][j];
                    break;
            }
            out << ' ';
        }
        out << '\n';
    }
    return out;
}