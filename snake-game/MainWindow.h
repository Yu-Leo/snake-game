#pragma once

#include <SFML/Graphics.hpp>

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

    void draw_cell(const Point& point, sf::RectangleShape& cell);

    void draw_field();
};

