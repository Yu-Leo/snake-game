#pragma once

#include <iostream>
#include <vector>

#include "Apple.h"
#include "Snake.h"

class GameField {
public:

    GameField();

    void move_snake();

    void turn_snake(int direction);

    int get_snake_direction() const;
    
private:

    enum Symbols {
        SNAKE = '#',
        NONE = '-',
        APPLE = '*'
    };

    static const int FIELD_CELL_TYPE_NONE = 0;
    static const int FIELD_CELL_TYPE_APPLE = -1;

    static const int DEFAULT_SIZE = 20;

    const int size = this->DEFAULT_SIZE; // Length of side of field

    std::vector<std::vector<int>> field;
    Snake snake;
    Apple apple;

    void resize_matrix();

    void init_field(); // Fill the matrix with VOID_SYMBOLs

    void check_collisions();

    void grow_snake();

    void decrease_snake_cells();

    void render_snake();

    void render_apple();

    bool is_cell_empty(const Point& cell);

    int count_empty_cells();

    Point get_random_empty_cell();

    friend std::ostream& operator<< (std::ostream& out, const GameField& game_field);
};

std::ostream& operator<< (std::ostream& out, const GameField& game_field);
