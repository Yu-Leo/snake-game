#pragma once

#include "Menu.h"
#include "Sounds.h"
#include "../mechanics/GameField.h"

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

    class Speed {
    public:

        void delay();

        int get_num() const;
        
        std::string get_active_item() const;

        void update(const MainWindow& window);

        void set_speed(std::string speed_item);

        void increase_speed();
        
        void reduce_speed();

    private:
        std::vector<std::string> speed_items = { "Auto", "1", "2", "3", "4", "5", "6" };

        int active_speed_item = 0;

        std::vector<int> delays = { 130, 110, 100, 90, 80, 65 };
        bool auto_speed = true;
        int speed = 0; // 0 - low, 5 - fast

        bool is_correct_speed_item(std::string speed_item);
        
    };
    
    Speed speed;

    int map_number = 0;

    Size window_size; // Size in ptx

    GameField game_field; // Mechanics of game
    Size game_field_size; // Size of game field in cells

    struct Textures {
        sf::Texture none, apple, super_apple, snake_head, snake_body, wall;
    };

    struct Sprites {
        sf::Sprite none, apple, super_apple, snake_head, snake_body, wall;
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

        void reset_active_item();

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

    void set_score_text_color();

    void handling_control(const sf::Event& event); // Processing controlling snake

    void handling_menu_navigation(const sf::Event& event); // Menu navigation processing

    void change_map(int new_map_num);

    void play_sounds(); // Check snake head collisions and play sounds 

    void draw_screen(); // Draw game field and title with score

    void draw_field(); // Draw game field

    void draw_cell(const Point& point);

    void rotate_snake_head_sprite();

    void draw_score_bar(); // Draw title with score
};
