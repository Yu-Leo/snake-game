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

	const sf::Color BACKGROUND_COLOR = sf::Color(220, 220, 220);
	const sf::Color TEXT_COLOR = sf::Color::Black;

	std::vector<sf::Text> main_menu_items;
	std::vector<std::string> main_menu_items_text = { "Start new game", "Settings", "Quit" };
	
	void set_font_settings();
};

