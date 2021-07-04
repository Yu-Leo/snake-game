#pragma once

#include <iostream>
#include <vector>

#include "Apple.h"
#include "Snake.h"
#include "Size.h"

class GameField {
public:

    static const int FIELD_CELL_TYPE_NONE = 0;
    static const int FIELD_CELL_TYPE_APPLE = -1;

    std::vector<std::vector<int>> field;

    GameField(const Size& size);

    GameField();

    void move_snake();

    void turn_snake(int direction); // Change snake direction

    int get_snake_direction() const;

    Size get_size() const;
    
private:

    enum Symbols { // Symbols for console display
        SNAKE = '#', // Cell with snake
        NONE = '-', // Empty cell
        APPLE = '*' // Cell with apple
    };

    Size size;
    
    Snake snake;
    Apple apple;

    void resize_matrix(); // Change sizes of field vectors

    void init_field(); // Fill the matrix with FIELD_CELL_TYPE_NONE

    void check_collisions(); // Check collisions snake head with other cells

    void grow_snake(); // Grow snake, if it eat apple

    void decrease_snake_cells(); // Decrease values of all snake's cells

    void render_snake(); // Fill snake's cells

    void render_apple(); // Fill apple's cell

    bool is_cell_empty(const Point& cell); // Is cell is empty

    int count_empty_cells();

    Point get_random_empty_cell();

    friend void print_cell(std::ostream& out, const GameField& game_field, const Point& cell);

    friend std::ostream& operator<< (std::ostream& out, const GameField& game_field);
};


void print_cell(std::ostream& out, const GameField& game_field, const Point& cell);

std::ostream& operator<< (std::ostream& out, const GameField& game_field);
