#pragma once

#include <SFML/Graphics.hpp>

#include "GameField.h"

#define CELL_SIZE 32 // Size of one cell in ptx

class MainWindow : public sf::RenderWindow { // Class of main game window
public:

    MainWindow(const Size& size); // Constructor with settable size

    void event_handling(); // Processing window's events 

    void one_iteration(); // One game iteration

    void redraw(); // Redraw game window
    
private:

    GameField game_field;

    struct Textures {
        sf::Texture none, apple, snake;
    };

    struct Sprites {
        sf::Sprite none, apple, snake;
    };

    Textures textures;

    Sprites sprites;
    
    void load_textures(); // Load textures images from files

    void set_textures(); // Set textures on sprites

    void draw_cell(const Point& point);

    void draw_field();
};

