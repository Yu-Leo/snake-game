#include <iostream>

#include "constants.h"
#include "GameField.h"

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
                game_field.turn_snake(Directions::UP);
                break;
            case 'a':
                game_field.turn_snake(Directions::LEFT);
                break;
            case 's':
                game_field.turn_snake(Directions::DOWN);
                break;
            case 'd':
                game_field.turn_snake(Directions::RIGHT);
                break;
            default:
                game = false;
                break;
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
