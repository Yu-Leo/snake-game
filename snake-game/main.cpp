#include <iostream>
#include <queue>

#include "constants.h"
#include "GameField.h"

int main() {
    srand(0);

    GameField game_field;

    bool game = true;

    std::queue<int> snake_directions;
    std::cout << game_field << '\n';
    while (game) {
        char command;
        std::cin >> command;
        int last_snake_direction = (snake_directions.empty() ?
            game_field.get_snake_direction() : snake_directions.front());
        
        switch (command) {
            case 'w':
                if (last_snake_direction != Directions::DOWN && snake_directions.size() < 2) {
                    snake_directions.push(Directions::UP);
                }
                break;
            case 'a':
                if (last_snake_direction != Directions::RIGHT && snake_directions.size() < 2) {
                    snake_directions.push(Directions::LEFT);
                }
                break;
            case 's':
                if (last_snake_direction != Directions::UP && snake_directions.size() < 2) {
                    snake_directions.push(Directions::DOWN);
                }
                break;
            case 'd':
                if (last_snake_direction != Directions::LEFT && snake_directions.size() < 2) {
                    snake_directions.push(Directions::RIGHT);
                }
                break;
            default:
                game = false;
                break;
        }

        if (!snake_directions.empty()) {
            game_field.turn_snake(snake_directions.front());
            snake_directions.pop();
        }

        try {
            game_field.move_snake();
            std::cout << game_field << '\n';
        } catch (const int& e) {
            game = false;
            std::cout << "Game over!\n";
        }
    }
    return 0;
}
