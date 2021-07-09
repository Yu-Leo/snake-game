#pragma once

#include <SFML/Graphics.hpp>

#include "GameField.h"
#include "Sounds.h"
#include "Menu.h"

#define CELL_SIZE 32 // Size of one cell in ptx

#define TOP_PADDING 55

class MainWindow : public sf::RenderWindow { // Class of main game window
public:

    MainWindow(const Size& size); // Constructor with settable size

    void event_handling(); // Processing window's events 

    void handling_control(const sf::Event& event); // Processing controlling

    void handling_menu_navigation(const sf::Event& event);

    void one_iteration(); // One game iteration

    void redraw(); // Redraw game window
    
    void delay();

private:
    int speed = 2; // 0 - low, 4 - fast

    Size size;

    GameField game_field;

    struct Textures {
        sf::Texture none, apple, snake, wall;
    };

    struct Sprites {
        sf::Sprite none, apple, snake, wall;
    };

    Textures textures;
    Sprites sprites;

    Sounds sounds;
    
    sf::Font font;
    
    sf::Text score_text;
    sf::Text game_over_text;

    Menu menu;

    const sf::Color BACKGROUND_COLOR = sf::Color(0, 0, 0);
    
    void load_textures(); // Load textures images from files

    void set_textures(); // Set textures on sprites

    void set_text_settings();

    void play_sounds(); // Check snake head collisions and play sounds 

    void draw_cell(const Point& point);

    void draw_field();

    void draw_score_bar();

    void draw_screen();

    void main_menu_operations();
};

