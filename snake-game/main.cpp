#include <iostream>

const int GAME_FIELD_SIZE = 20;

struct Point {
    int x, y;

    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Snake {
public:
    Snake() {
        this->init_snake_dots();
        this->size = this->DEFAULT_SIZE;
    }

    Point get_point_by_index(int index) { // Get point by it's index in dots list
        return this->dots[index];
    }

    int get_size() {
        return this->size;
    }

private:
    static const int DEFAULT_SIZE = 3;
    Point dots[GAME_FIELD_SIZE * GAME_FIELD_SIZE];
    int size;

    void init_snake_dots() { // Init snake in (0, 0), (1, 0), (2, 0)
        for (int i = 0; i < this->DEFAULT_SIZE; i++) {
            dots[i] = Point(this->DEFAULT_SIZE - i - 1, 0);
        }
    }
};

class GameField {
public:
    GameField() {
        this->init_field();
    }

    void render_snake() {
        for (int i = 0; i < this->snake.get_size(); i++) {
            Point dot = this->snake.get_point_by_index(i);
            this->field[dot.y][dot.x] = this->SNAKE_SYMBOL;
        }
    }

    void print_field() { // Print matrix to console (std::cout)
        for (int i = 0; i < GAME_FIELD_SIZE; i++) {
            for (int j = 0; j < GAME_FIELD_SIZE; j++) {
                std::cout << this->field[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    static const int SNAKE_SYMBOL = 1;
    static const int VOID_SYMBOL = 0;

    int field[GAME_FIELD_SIZE][GAME_FIELD_SIZE]; // Matrix of game field
    Snake snake;

    void init_field() { // Fill the matrix with VOID_SYMBOLs
        for (int i = 0; i < GAME_FIELD_SIZE; i++) {
            for (int j = 0; j < GAME_FIELD_SIZE; j++) {
                this->field[i][j] = this->VOID_SYMBOL;
            }
        }
    }
};

int main() {
    GameField game_field;
    game_field.render_snake();
    game_field.print_field();
    return 0;
}