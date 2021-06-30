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
    static const char SNAKE_SYMBOL = '#';
    static const char VOID_SYMBOL = '-';
    static const char APPLE_SYMBOL = '*';

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

    int get_random_empty_cell();

    friend std::ostream& operator<< (std::ostream& out, const GameField& game_field);
};

std::ostream& operator<< (std::ostream& out, const GameField& game_field);
