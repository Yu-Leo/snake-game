#pragma once

#include <iostream>
#include <vector>

#include "constants.h"
#include "Apple.h"
#include "Snake.h"

class GameField {
public:
    GameField();

    void update();

    void move_snake();

    void check_collision_with_apple();

    bool is_game_over();

    void turn_snake(int direction);

private:
    static const char SNAKE_SYMBOL = '#';
    static const char VOID_SYMBOL = '-';
    static const char APPLE_SYMBOL = '*';

    const int size = GAME_FIELD_SIZE;

    std::vector<std::vector<char>> field;
    Snake snake;
    Apple apple;

    void resize_matrix();

    void init_field(); // Fill the matrix with VOID_SYMBOLs

    bool check_collision_with_snake_body();

    bool check_collision_with_borders();

    void render_snake();

    void render_apple();

    std::vector<Point> generate_acceptable_points_for_new_apple();

    friend std::ostream& operator<< (std::ostream& out, const GameField& game_field);
};

std::ostream& operator<< (std::ostream& out, const GameField& game_field);
