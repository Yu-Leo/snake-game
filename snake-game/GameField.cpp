#include "GameField.h"

#include <algorithm>

#include "Apple.h"
#include "Snake.h"
#include "RandomPoint.h"

GameField::GameField() {
    RandomPoint rp(this->generate_acceptable_points_for_new_apple());
    this->apple = Apple(rp);
    this->init_field();
    this->render_snake();
    this->render_apple();
}

void GameField::update() {
    this->init_field(); // Clear matrix
    this->render_apple();
    this->render_snake();
}

void GameField::move_snake() {
    this->snake.move();
}

void GameField::check_collision_with_apple() {
    if (this->snake.get_point_by_index(0) == this->apple.get_coordinates()) {
        this->snake.increase_size();

        RandomPoint rp(this->generate_acceptable_points_for_new_apple());
        this->apple = Apple(rp);
    }
}

bool GameField::is_game_over() {
    return this->check_collision_with_snake_body() ||
        this->check_collision_with_borders();
}

void GameField::turn_snake(int direction) {
    this->snake.change_direction(direction);
}

void GameField::resize_matrix() {
    this->field.resize(this->size);
    for (int i = 0; i < this->size; i++) {
        this->field[i].resize(this->size);
    }
}

void GameField::init_field() { // Fill the matrix with VOID_SYMBOLs
    this->resize_matrix();

    for (int i = 0; i < GAME_FIELD_SIZE; i++) {
        for (int j = 0; j < GAME_FIELD_SIZE; j++) {
            this->field[i][j] = this->VOID_SYMBOL;
        }
    }
}

bool GameField::check_collision_with_snake_body() {
    return this->snake.check_collision_with_body();
}

bool GameField::check_collision_with_borders() {
    Point head = this->snake.get_point_by_index(0);
    return (head.x < 0 || head.x > GAME_FIELD_SIZE ||
        head.y < 0 || head.y > GAME_FIELD_SIZE);
}

void GameField::render_snake() {
    for (int i = 0; i < this->snake.get_size(); i++) {
        Point dot = this->snake.get_point_by_index(i);
        this->field[dot.y][dot.x] = this->SNAKE_SYMBOL;
    }
}

void GameField::render_apple() {
    Point dot = this->apple.get_coordinates();
    this->field[dot.y][dot.x] = this->APPLE_SYMBOL;
}

std::vector<Point> GameField::generate_acceptable_points_for_new_apple() {
    std::vector<Point> unacceptable_points = this->snake.get_points();
    std::vector<int> unacceptable_nums;
    for (Point p : unacceptable_points) {
        unacceptable_nums.push_back(p.y * GAME_FIELD_SIZE + p.x);
    }
    unacceptable_nums.push_back(-1);
    unacceptable_nums.push_back((GAME_FIELD_SIZE - 1) * (GAME_FIELD_SIZE - 1) + 1);
    std::sort(unacceptable_nums.begin(), unacceptable_nums.end());

    std::vector<Point> acceptable_points;
    for (int i = 0; i < unacceptable_nums.size() - 1; i++) {
        for (int j = unacceptable_nums[i]; j < unacceptable_nums[i + 1]; j++) {
            acceptable_points.push_back(Point(j % GAME_FIELD_SIZE, j / GAME_FIELD_SIZE));
        }
    }
    return acceptable_points;
}

std::ostream& operator<< (std::ostream& out, const GameField& game_field) {
    for (int i = 0; i < GAME_FIELD_SIZE; i++) {
        for (int j = 0; j < GAME_FIELD_SIZE; j++) {
            out << game_field.field[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}