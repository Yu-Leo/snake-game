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
        
        game_field.move_snake();
        /*
        game_field.check_collision_with_apple();
        
        if (game_field.is_game_over()) {
            std::cout << "Game over!\n";
            game = false;
        } else {
            game_field.update();
            std::cout << game_field << '\n';
        }
        */
        std::cout << game_field << '\n';
    }
    return 0;
}
