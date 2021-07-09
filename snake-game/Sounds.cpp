#include "Sounds.h"

Sounds::Sounds() {
    this->load_sound_buffers();
    this->set_sound_buffers();
    this->set_volume();
}

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
        case this->MENU_NAVIGATE:
            this->menu_navigate.play();
            break;
    }
}

int Sounds::get_volume() {
    return this->volume;
}

void Sounds::turn_up_volume() {
    this->volume += 5;
    if (this->volume > this->MAX_VOLUME)
        this->volume = this->MAX_VOLUME;
    this->set_volume();
}

void Sounds::turn_down_volume() {
    this->volume -= 5;
    if (this->volume < this->MIN_VOLUME)
        this->volume = this->MIN_VOLUME;
    this->set_volume();
}

void Sounds::load_sound_buffers() {
    this->sound_buffers.ate_apple.loadFromFile("./sounds/ate_apple.wav");
    this->sound_buffers.collision_with_wall.loadFromFile("./sounds/collision_with_wall.wav");
    this->sound_buffers.collision_with_body.loadFromFile("./sounds/collision_with_body.wav");
    this->sound_buffers.menu_navigate.loadFromFile("./sounds/menu_navigate.wav");

}

void Sounds::set_sound_buffers() {
    this->ate_apple.setBuffer(this->sound_buffers.ate_apple);
    this->collision_with_wall.setBuffer(this->sound_buffers.collision_with_wall);
    this->collision_with_body.setBuffer(this->sound_buffers.collision_with_body);
    this->menu_navigate.setBuffer(this->sound_buffers.menu_navigate);
}

void Sounds::set_volume() {
    this->ate_apple.setVolume(this->volume);
    this->collision_with_wall.setVolume(this->volume);
    this->collision_with_body.setVolume(this->volume);
    this->menu_navigate.setVolume(this->volume);
}