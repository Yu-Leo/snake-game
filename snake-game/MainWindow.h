#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        sf::Texture none, apple, snake, wall;
    };

    struct Sprites {
        sf::Sprite none, apple, snake, wall;
    };

    struct SoundBuffers {
        sf::SoundBuffer ate_apple, collision_with_wall, collision_with_body;
    };

    struct Sounds {
        sf::Sound ate_apple, collision_with_wall, collision_with_body;
    };

    Textures textures;
    Sprites sprites;

    SoundBuffers sound_buffers;
    Sounds sounds;

    void load_textures(); // Load textures images from files

    void set_textures(); // Set textures on sprites

    void load_sound_buffers(); // Load sound buffers from files
    
    void set_sound_buffers(); // Set sound buffers on sounds

    void play_sounds(); // Check snake head collisions and play sounds 

    void draw_cell(const Point& point);

    void draw_field();
};

