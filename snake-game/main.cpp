#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>

#include "MainWindow.h"

#define RANDOM_GENERATING true // (true/false)

int main() {

#if RANDOM_GENERATING
    srand(std::time(NULL)); // Set current time as seed for png
#else
    srand(0); // Set seed for pseudorandom number generator
#endif

    MainWindow window(Size(35, 20));
    
    while (window.isOpen()) {
        window.event_handling();
        window.one_iteration();
        window.redraw();
        sf::sleep(sf::milliseconds(110));
    }

    return 0;
}
