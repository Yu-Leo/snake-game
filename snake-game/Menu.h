#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Size.h"

class Menu { // Class of game menu
public:

	Menu();

	void set_text_to_items(const std::vector<std::string>& items); // Set title of menu items

	void set_text_to_item(int index, const std::string& text); // Set title of menu item

	void draw(sf::RenderWindow &window); // Display menu

	void next_item(); // Switch to next item in items list
	
	void previous_item(); // Switch to previous item in items list

	int get_active_item_index(); // Getter for active item index

private:

	struct Position { // Position of any menu elements
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

	std::vector<sf::Text> menu_items;
	std::vector<std::string> menu_items_text;
	
	int active_item_index = 0;

	void load_font(); // Load font from file

	void set_font_settings(); // Set font settings to menu items

	void set_texts(); // Set titles to menu items

	Size get_background_size(); // Calculate size of background rectangle

	void draw_background(sf::RenderWindow& window, const Size& size,
		const Position& pos);

	void draw_items(sf::RenderWindow& window, const Position& bg_pos);
};

