#include "Sounds.h"

void Sounds::play(int sound_name) {
    switch (sound_name) {
        case this->ATE_APPLE:
            this->ate_apple.play();
            break;
        case this->COLLISION_WITH_BODY:
            this->collision_with_body.play();
            break;
        case this->COLLISION_WITH_WALL:
            this->collision_with_wall.play();
            break;
    }
}

void Sounds::load_sound_buffers() {
    this->sound_buffers.ate_apple.loadFromFile("./sounds/ate_apple.wav");
    this->sound_buffers.collision_with_wall.loadFromFile("./sounds/collision_with_wall.wav");
    this->sound_buffers.collision_with_body.loadFromFile("./sounds/collision_with_body.wav");
}

void Sounds::set_sound_buffers() {
    this->ate_apple.setBuffer(this->sound_buffers.ate_apple);
    this->collision_with_wall.setBuffer(this->sound_buffers.collision_with_wall);
    this->collision_with_body.setBuffer(this->sound_buffers.collision_with_body);
}