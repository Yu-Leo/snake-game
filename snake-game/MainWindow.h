#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

#include "GameField.h"
#include "Sounds.h"

#define CELL_SIZE 32 // Size of one cell in ptx

#define TOP_PADDING 55

class MainWindow : public sf::RenderWindow { // Class of main game window
public:

    MainWindow(const Size& size); // Constructor with settable size

    void event_handling(); // Processing window's events 

    void one_iteration(); // One game iteration

    void redraw(); // Redraw game window
    
    void delay();

private:
    int speed = 0; // 0 - low, 4 - fast

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
    sf::Font menu_font;

    sf::Text score_text;
    sf::Text game_over_text;

    const sf::Color BACKGROUND_COLOR = sf::Color(0, 0, 0);

    std::vector<sf::Text> main_menu_items;
    std::vector<std::string> main_menu_items_text = {"Start new game", "Settings", "Quit"};
    
    void load_textures(); // Load textures images from files

    void set_textures(); // Set textures on sprites

    void set_text_settings();

    void play_sounds(); // Check snake head collisions and play sounds 

    void draw_cell(const Point& point);

    void draw_field();

    void draw_score_bar();

    void draw_screen();

    void draw_menu();
};

