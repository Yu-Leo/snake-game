#pragma once

#include <iostream>
#include <vector>
#include <queue>

#include "SuperApple.h"
#include "Snake.h"
#include "Size.h"
#include "MapsList.h"

#define CHANCE_OF_GENERATING_SUPER_APPLE 15 // in %

static Size DEFAULT_SIZE = Size(35, 20);

const MapsList MAPS(DEFAULT_SIZE);

class GameField {
public:

    enum class GameStatus {
        STARTED,
        ACTIVE,
        PAUSE,
        FINISHED
    };

    enum class CellTypes {
        NONE,
        APPLE,
        SUPER_APPLE,
        SNAKE_HEAD,
        SNAKE_BODY,
        WALL
    };

    enum class Collisions {
        APPLE,
        SUPER_APPLE,
        BODY,
        WALL,
        NONE
    };

    GameField(const Size& size, int map_number=0, bool only_walls=false); // Constructor with settable size

    GameField(); // Constructor with default size

    void one_iteration(); // Processing snake movement

    void key_pressed(); // Update last snake direction. Needs to call before changing snake direction

    void insert_command(int direction); // Processing new changing direction command 

    void start();

    void finish(); // Exit frome game (game over)

    void pause();

    void unpause();

    void clear_collision();

    Collisions get_collision() const;

    int get_score() const; // Getter for score

    Size get_size() const; // Getter for game_field size

    int get_cells_without_walls() const;

    int get_snake_direction() const;

    GameStatus get_game_status() const; // Getter for game status

    CellTypes get_cell_type(const Point& point) const; // Get type of specified cell

private:

    static const int FIELD_CELL_TYPE_NONE = 0;
    static const int FIELD_CELL_TYPE_APPLE = -1;
    static const int FIELD_CELL_TYPE_SUPER_APPLE = -2;
    static const int FIELD_CELL_TYPE_WALL = -3;

    int score = 0;
    int cells_without_walls;

    Size size; // Size of game field
    std::vector<std::vector<int>> field; // Raw field

    Snake snake;
    Apple apple;

    std::queue<int> snake_directions; // Queue of controlling commands
    int last_snake_direction;

    GameStatus game_status; // Is player in gameplay

    Collisions collision = Collisions::NONE;

    void init_field(); // Fill the matrix with FIELD_CELL_TYPE_NONE

    void resize_matrix(); // Change sizes of field vectors

    void set_map(const Map& map); // Add walls to field

    void render_snake(); // Fill snake's cells

    int count_cells_without_walls();

    void move_snake(); // Move the snake by one cell

    void turn_snake(); // Change snake direction

    void check_collisions(); // Check collisions snake head with other cells

    void increase_length();

    void generate_new_apple();

    void grow_snake(); // Grow snake, if it eat apple

    void decrease_snake_cells(); // Decrease values of all snake's cells

    bool is_cell_empty(const Point& cell); // Is cell is empty

    int count_empty_cells();

    Point get_random_empty_cell();
};
