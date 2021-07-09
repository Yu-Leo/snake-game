#pragma once

#include <SFML/Audio.hpp>

class Sounds {
public:

    enum SoundNames {
        ATE_APPLE,
        COLLISION_WITH_BODY,
        COLLISION_WITH_WALL,
        MENU_NAVIGATE
    };

    Sounds();

    void play(int sound_name); // Play sound by it's name
    
    int get_volume();

    void turn_up_volume();

    void turn_down_volume();

private:

    const int MAX_VOLUME = 100;
    const int MIN_VOLUME = 0;

    int volume = 10;

    struct SoundBuffers {
        sf::SoundBuffer ate_apple;
        sf::SoundBuffer collision_with_wall;
        sf::SoundBuffer collision_with_body;
        sf::SoundBuffer menu_navigate;
    };

    SoundBuffers sound_buffers;

    sf::Sound ate_apple; 
    sf::Sound collision_with_wall;
    sf::Sound collision_with_body;
    sf::Sound menu_navigate;

    void load_sound_buffers(); // Load sound buffers from files

    void set_sound_buffers(); // Set sound buffers on sounds

    void set_volume();
};

