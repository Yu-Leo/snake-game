#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
	Menu() {
		this->set_font_settings();
	}

	void draw_main_menu(sf::RenderWindow &window);

private:
	sf::Font font;

	std::vector<sf::Text> main_menu_items;
	std::vector<std::string> main_menu_items_text = { "Start new game", "Settings", "Quit" };
	
	void set_font_settings();
};

