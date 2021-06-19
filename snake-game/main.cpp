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

    // Constants of directions
    static const int RIGHT = 0;
    static const int DOWN = 1;
    static const int LEFT = 2;
    static const int UP = 3;

    Snake() {
        this->init_snake_dots();
        this->size = this->DEFAULT_SIZE;
        this->direction = this->RIGHT;
    }

    Point get_point_by_index(int index) { // Get point by it's index in dots list
        return this->dots[index];
    }

    int get_size() {
        return this->size;
    }

    void move() {
        for (int i = this->size; i > 0; i--) {
            this->dots[i] = this->dots[i - 1];
        }

        switch (this->direction) {
            case this->RIGHT:
                dots[0].x++;
                break;
            case this->DOWN:
                dots[0].y++;
                break;
            case this->LEFT:
                dots[0].x--;
                break;
            case this->UP:
                dots[0].y--;
                break;
            default:
                break;
        }
    }

    void change_direction(int new_direction) {
        if (!this->is_change_of_direction_correct(new_direction)) {
            std::cout << "error\n";
            return;
        }

        this->direction = new_direction;
    }

private:
    static const int DEFAULT_SIZE = 3;

    Point dots[GAME_FIELD_SIZE * GAME_FIELD_SIZE];
    int size;
    int direction;

    void init_snake_dots() { // Init snake in (0, 0), (1, 0), (2, 0)
        for (int i = 0; i < this->DEFAULT_SIZE; i++) {
            dots[i] = Point(this->DEFAULT_SIZE - i - 1, 0);
        }
    }

    bool is_change_of_direction_correct(int new_direction) {
        bool correct_value = (
            new_direction == this->RIGHT ||
            new_direction == this->DOWN ||
            new_direction == this->LEFT ||
            new_direction == this->UP);

        // Snake can't change direction to opposit sharply
        bool check_from_left =
            (this->direction == this->LEFT && new_direction != this->RIGHT);
        bool check_from_right =
            (this->direction == this->RIGHT && new_direction != this->LEFT);
        bool check_from_up =
            (this->direction == this->UP && new_direction != this->DOWN);
        bool check_from_down =
            (this->direction == this->DOWN && new_direction != this->UP);

        return (correct_value && (check_from_left || check_from_right ||
            check_from_up || check_from_down));
    }
};

class GameField {
public:
    GameField() {
        this->init_field();
    }

    void render_snake() {
        this->init_field(); // Clear matrix
        // Draw snake
        for (int i = 0; i < this->snake.get_size(); i++) {
            Point dot = this->snake.get_point_by_index(i);
            this->field[dot.y][dot.x] = this->SNAKE_SYMBOL;
        }
    }

    void move_snake() {
        this->snake.move();
    }

    void turn_snake(int direction) {
        this->snake.change_direction(direction);
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
    bool game = true;

    game_field.render_snake();
    game_field.print_field();
    std::cout << "\n";

    while (game) {
        char command;
        std::cin >> command;

        switch (command) {
            case 'w':
                game_field.turn_snake(Snake::UP);
                break;
            case 'a':
                game_field.turn_snake(Snake::LEFT);
                break;
            case 's':
                game_field.turn_snake(Snake::DOWN);
                break;
            case 'd':
                game_field.turn_snake(Snake::RIGHT);
                break;
            default:
                game = false;
                break;
        }
        game_field.move_snake();
        game_field.render_snake();
        game_field.print_field();
        std::cout << "\n";
    }
    return 0;
}