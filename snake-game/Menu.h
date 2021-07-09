#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Size.h"

class Menu {
public:
	Menu() {
		this->set_font_settings();
	}

	void draw_main_menu(sf::RenderWindow &window);

	void next_item();
	
	void previous_item();

	int get_active_item_index();

private:

	struct Position {
		float x = 0;
		float y = 0;

		Position() {}

		Position(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};

	const float HORIZONTAL_PADDING = 40.0;
	const float VERTICAL_PADDING = 30.0;
	const float ITEM_PADDING = 20;

	sf::Font font;

	const sf::Color BACKGROUND_COLOR = sf::Color(220, 220, 220);
	const sf::Color INACTIVE_TEXT_COLOR = sf::Color(128, 128, 128);
	const sf::Color ACTIVE_TEXT_COLOR = sf::Color::Black;

	std::vector<sf::Text> main_menu_items;
	std::vector<std::string> main_menu_items_text = { "Start new game", "Settings", "Quit" };
	
	int active_item_index = 0;

	void set_font_settings();

	Size get_background_size();

	void draw_background(sf::RenderWindow& window, const Size& size, const Position& pos);

	void draw_items(sf::RenderWindow& window, const Position& bg_pos);
};

