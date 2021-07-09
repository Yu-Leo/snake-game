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

    Sounds() {
        this->load_sound_buffers();
        this->set_sound_buffers();
    }

    void play(int sound_name); // Play sound by it's name
    

private:
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
};

