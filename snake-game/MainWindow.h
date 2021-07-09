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
    
    void delay();

private:

    int speed = 2; // 0 - low, 4 - fast

    Size window_size;

    GameField game_field;
    Size game_field_size;

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
    
    struct MenuList {
    public:

        enum ActiveMenu {
            MAIN,
            PAUSE,
            SETTINGS
        };

        int active_menu = MAIN;

        Menu main_menu;
        Menu pause_menu;
        Menu settings_menu;

        MenuList() {
            std::vector<std::string> main_menu_items = { "Start new game", "Settings", "Quit" };
            std::vector<std::string> pause_menu_items = { "Resume game", "Settings", "Quit" };
            std::vector<std::string> settings_menu_items = { "Back to main menu", "Volume" };
            
            this->main_menu.set_text_to_items(main_menu_items);
            this->pause_menu.set_text_to_items(pause_menu_items);
            this->settings_menu.set_text_to_items(settings_menu_items);
        }
        
        void operations(MainWindow& window);

        void next_item();

        void previous_item();

    private:

        void main_menu_operations(MainWindow& window);

        void pause_menu_operations(MainWindow& window);

        void settings_menu_operations(MainWindow& window);
    };

    MenuList menu;

    const sf::Color BACKGROUND_COLOR = sf::Color(0, 0, 0);
    
    void load_textures(); // Load textures images from files

    void set_textures(); // Set textures on sprites

    void set_text_settings();

    void play_sounds(); // Check snake head collisions and play sounds 

    void draw_cell(const Point& point);

    void draw_field();

    void draw_score_bar();

    void draw_screen();

    void handling_control(const sf::Event& event); // Processing controlling

    void handling_menu_navigation(const sf::Event& event);
};

