#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>


#include "GameField.h"

#define CELL_SIZE 32

#define RANDOM_GENERATING false // (true/false)

void draw_field(sf::RenderWindow& window, const GameField &game_field) {
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (int i = 0; i < game_field.get_size().height; i++) {
        for (int j = 0; j < game_field.get_size().width; j++) {
            switch (game_field.field[i][j]) {
                case GameField::FIELD_CELL_TYPE_NONE:
                    cell.setPosition(float(j * CELL_SIZE), float(i * CELL_SIZE));
                    cell.setFillColor(sf::Color::Black);
                    window.draw(cell);
                    break;
                case GameField::FIELD_CELL_TYPE_APPLE:
                    cell.setPosition(float(j * CELL_SIZE), float(i * CELL_SIZE));
                    cell.setFillColor(sf::Color::Red);
                    window.draw(cell);
                    break;
                default:
                    cell.setPosition(float(j * CELL_SIZE), float(i * CELL_SIZE));
                    cell.setFillColor(sf::Color::Green);
                    window.draw(cell);
                    break;
            }
        }
    }
}


int main() {

#if RANDOM_GENERATING
    srand(std::time(NULL)); // Set current time as seed for png
#else
    srand(0); // Set seed for pseudorandom number generator
#endif

    GameField game_field(Size(35, 20));
    
    int window_width = game_field.get_size().width * CELL_SIZE;
    int window_height = game_field.get_size().height * CELL_SIZE;

    sf::RenderWindow main_window(
        sf::VideoMode(window_width, window_height),
        "Snake game",
        sf::Style::Close);

    while (main_window.isOpen()) {
        sf::Event event;
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                main_window.close();
            if (event.type == sf::Event::KeyPressed) {
                game_field.key_pressed();
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    game_field.insert_command(Snake::Directions::UP);
                    break;
                case sf::Keyboard::Right:
                    game_field.insert_command(Snake::Directions::RIGHT);
                    break;
                case sf::Keyboard::Down:
                    game_field.insert_command(Snake::Directions::DOWN);
                    break;
                case sf::Keyboard::Left:
                    game_field.insert_command(Snake::Directions::LEFT);
                    break;
                case sf::Keyboard::Escape:
                    game_field.finish_game();
                default:
                    break;
                }
            }
        }
        game_field.one_iteration();

        if (game_field.get_game_status()) {
            main_window.clear(sf::Color(183, 212, 168));
            draw_field(main_window, game_field);
            main_window.display();
        } else {
            main_window.close();
        }

        sf::sleep(sf::milliseconds(100));
    }
    return 0;
}
