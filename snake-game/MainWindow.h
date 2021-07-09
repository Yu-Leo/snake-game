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

    void one_iteration(); // One game iteration

    void redraw(); // Redraw game window
    
    void delay(); // Delay after one game iteration

private:

    int speed = 2; // 0 - low, 4 - fast

    bool field_regeneration = false; // Should the field be regenerated

    Size window_size; // Size in ptx

    GameField game_field; // Mechanics of game
    Size game_field_size; // Size of game field in cells

    struct Textures {
        sf::Texture none, apple, snake, wall;
    };

    struct Sprites {
        sf::Sprite none, apple, snake, wall;
    };

    Textures textures;
    Sprites sprites;

    Sounds sounds;
    
    sf::Font font; // Font for titles
    
    sf::Text score_text;
    sf::Text game_over_text;
    
    struct MenuList {
    public:

        enum ActiveMenu {
            NONE,
            MAIN,
            PAUSE,
            SETTINGS
        };

        int active = MAIN;

        Menu main;
        Menu pause;
        Menu settings;

        MenuList();
        
        void draw(MainWindow& window); // Draw menu at window

        void operations(MainWindow& window);

        void next_item(); // Switch to next item in items list

        void previous_item(); // Switch to previous item in items list

    private:

        void main_menu_operations(MainWindow& window);

        void pause_menu_operations(MainWindow& window);

        void settings_menu_operations(MainWindow& window);
    };

    MenuList menu;

    const sf::Color BACKGROUND_COLOR = sf::Color(0, 0, 0);
    
    void load_textures(); // Load textures images from files

    void set_textures(); // Set textures on sprites

    void set_text_settings(); // Set settings of text

    void play_sounds(); // Check snake head collisions and play sounds 

    void draw_cell(const Point& point);

    void draw_field(); // Draw game field

    void draw_score_bar(); // Draw title with score

    void draw_screen(); // Draw game field and title with score

    void handling_control(const sf::Event& event); // Processing controlling snake

    void handling_menu_navigation(const sf::Event& event); // Menu navigation processing
};
