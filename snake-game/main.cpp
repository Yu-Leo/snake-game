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

    bool operator==(const Point& other) {
        return this->x == other.x && this->y == other.y;
    }
};

std::ostream& operator<< (std::ostream& out, const Point& point) {
    out << '(' << point.x << ", " << point.y << ')';
    return out;
}

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

    bool check_collision_with_body() { // It's snake eating itself
        for (int i = 0; i < this->size; i++) {
            if (i > 3 && dots[i] == dots[0]) {
                return true;
            }
        }
        return false;
    }

    void increase_size() {
        this->size++;
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

class Apple {
public:
    Apple() {
        coordinates = Point(this->generate_random_coord(),
            this->generate_random_coord());
    }

    Apple(int x, int y) {
        coordinates = Point(x, y);
    }

    Point get_coordinates() {
        return coordinates;
    }

private:
    Point coordinates;

    int generate_random_coord() {
        return rand() % (GAME_FIELD_SIZE + 1);
    }
};

class GameField {
public:
    GameField() {
        this->apple = Apple();
        this->init_field();
        this->render_snake();
        this->render_apple();
    }

    void update() {
        this->init_field(); // Clear matrix
        this->render_apple();
        this->render_snake();
    }

    void move_snake() {
        this->snake.move();
    }

    void check_collision_with_apple() {
        if (this->snake.get_point_by_index(0) == this->apple.get_coordinates()) {
            this->snake.increase_size();
            this->apple = Apple();
        }
    }

    bool check_collision_with_snake_body() {
        return this->snake.check_collision_with_body();
    }

    bool check_collision_with_borders() {
        Point head = this->snake.get_point_by_index(0);
        return (head.x < 0 || head.x > GAME_FIELD_SIZE ||
            head.y < 0 || head.y > GAME_FIELD_SIZE);
    }

    void turn_snake(int direction) {
        this->snake.change_direction(direction);
    }

private:
    static const char SNAKE_SYMBOL = '#';
    static const char VOID_SYMBOL = '-';
    static const char APPLE_SYMBOL = '*';

    char field[GAME_FIELD_SIZE][GAME_FIELD_SIZE]; // Matrix of game field
    Snake snake;
    Apple apple;

    void init_field() { // Fill the matrix with VOID_SYMBOLs
        for (int i = 0; i < GAME_FIELD_SIZE; i++) {
            for (int j = 0; j < GAME_FIELD_SIZE; j++) {
                this->field[i][j] = this->VOID_SYMBOL;
            }
        }
    }

    void render_snake() {
        for (int i = 0; i < this->snake.get_size(); i++) {
            Point dot = this->snake.get_point_by_index(i);
            this->field[dot.y][dot.x] = this->SNAKE_SYMBOL;
        }
    }

    void render_apple() {
        Point dot = this->apple.get_coordinates();
        this->field[dot.y][dot.x] = this->APPLE_SYMBOL;
    }

    friend std::ostream& operator<< (std::ostream& out, const GameField& game_field);
};

std::ostream& operator<< (std::ostream& out, const GameField& game_field) {
    for (int i = 0; i < GAME_FIELD_SIZE; i++) {
        for (int j = 0; j < GAME_FIELD_SIZE; j++) {
            out << game_field.field[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

int main() {
    srand(0);

    GameField game_field;
    bool game = true;

    std::cout << game_field << '\n';
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
        game_field.check_collision_with_apple();

        if (game_field.check_collision_with_snake_body() ||
            game_field.check_collision_with_borders()) {

            std::cout << "Game over!\n";
            game = false;
        }
        else {
            game_field.update();
            std::cout << game_field << '\n';
        }

    }
    return 0;
}