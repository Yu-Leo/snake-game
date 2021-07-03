#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>
#include <queue>

#include "GameField.h"

#define RANDOM_GENERATING false // (true/false)

int main() {

#if RANDOM_GENERATING
    srand(std::time(NULL)); // Set current time as seed for png
#else
    srand(0); // Set seed for pseudorandom number generator
#endif

    GameField game_field;
    bool game = true; // Is player in gameplay
    std::queue<int> snake_directions;
    std::cout << game_field << '\n';
    while (game) { // Main game cycle
        char command;
        std::cin >> command;
        int last_snake_direction = (snake_directions.empty() ?
            game_field.get_snake_direction() : snake_directions.front());
        
        switch (command) { // Processing of control commands
            case 'w': // Turn up
                if (last_snake_direction != Snake::Directions::DOWN && snake_directions.size() < 2) {
                    snake_directions.push(Snake::Directions::UP);
                }
                break;
            case 'a': // Turn to the left
                if (last_snake_direction != Snake::Directions::RIGHT && snake_directions.size() < 2) {
                    snake_directions.push(Snake::Directions::LEFT);
                }
                break;
            case 's': // Turn down
                if (last_snake_direction != Snake::Directions::UP && snake_directions.size() < 2) {
                    snake_directions.push(Snake::Directions::DOWN);
                }
                break;
            case 'd': // Turn to the right
                if (last_snake_direction != Snake::Directions::LEFT && snake_directions.size() < 2) {
                    snake_directions.push(Snake::Directions::RIGHT);
                }
                break;
            default:
                game = false;
                break;
        }

        // Processing changing direction
        if (!snake_directions.empty()) {
            game_field.turn_snake(snake_directions.front());
            snake_directions.pop();
        }

        // Snake movement
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
