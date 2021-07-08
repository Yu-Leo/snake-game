#pragma once

#include <SFML/Audio.hpp>

class Sounds {
public:

    enum SoundNames {
        ATE_APPLE,
        COLLISION_WITH_BODY,
        COLLISION_WITH_WALL
    };

    Sounds() {
        this->load_sound_buffers();
        this->set_sound_buffers();
    }

    void play(int sound_name); // Play sound by it's name
    

private:
    struct SoundBuffers {
        sf::SoundBuffer ate_apple, collision_with_wall, collision_with_body;
    };

    SoundBuffers sound_buffers;

    sf::Sound ate_apple, collision_with_wall, collision_with_body;

    void load_sound_buffers(); // Load sound buffers from files

    void set_sound_buffers(); // Set sound buffers on sounds
};

