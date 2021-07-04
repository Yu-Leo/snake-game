#pragma once

#include <SFML/Graphics.hpp>

#include "GameField.h"

#define CELL_SIZE 32 // Size of one cell in ptx

class MainWindow : public sf::RenderWindow {
public:
    MainWindow(const Size& size);

    void event_handling();

    void one_iteration();

    void redraw();
    
private:

    GameField game_field;

    void draw_field();
};

