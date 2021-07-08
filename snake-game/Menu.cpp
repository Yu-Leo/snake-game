#include "Menu.h"

Size Menu::get_background_size() {
    float current_menu_item_y = 0;
    float menu_item_max_width = 0;

    for (int i = 0; i < this->main_menu_items.size(); i++) {
        current_menu_item_y += this->main_menu_items[i].getLocalBounds().height + this->ITEM_PADDING;
        menu_item_max_width = std::max(menu_item_max_width, this->main_menu_items[i].getLocalBounds().width);
    }

    return Size(menu_item_max_width + this->HORIZONTAL_PADDING * 2,
        current_menu_item_y - this->ITEM_PADDING + this->VERTICAL_PADDING * 2);

}

void Menu::draw_background(sf::RenderWindow& window, const Size &size, const Position &pos) {
    sf::RectangleShape menu_rect(sf::Vector2f(size.width, size.height));
    menu_rect.setPosition(pos.x, pos.y);
    menu_rect.setFillColor(this->BACKGROUND_COLOR);
    window.draw(menu_rect);
}

void Menu::draw_items(sf::RenderWindow& window, const Position& bg_pos) {

    float current_y_pos = 0.0;
    for (int i = 0; i < this->main_menu_items.size(); i++) {
        sf::Color fill_color = (this->current_item_index == i ?
            this->ACTIVE_TEXT_COLOR : this->INACTIVE_TEXT_COLOR);

        this->main_menu_items[i].setFillColor(fill_color);

        this->main_menu_items[i].setPosition(bg_pos.x + this->HORIZONTAL_PADDING,
            bg_pos.y + this->VERTICAL_PADDING + current_y_pos);

        current_y_pos += this->main_menu_items[i].getLocalBounds().height +
            this->ITEM_PADDING;

        window.draw(this->main_menu_items[i]);
    }
}

void Menu::draw_main_menu(sf::RenderWindow& window) {
    Size background_size = this->get_background_size();
    Position background_pos((window.getSize().x - background_size.width) / 2,
        (window.getSize().y - background_size.height) / 2);

    this->draw_background(window, background_size, background_pos);
    
    this->draw_items(window, background_pos);
}

void Menu::set_font_settings() {
    this->font.loadFromFile("./fonts/menu_font.ttf");

    for (int i = 0; i < this->main_menu_items_text.size(); i++) {
        this->main_menu_items.push_back(sf::Text());
        this->main_menu_items.back().setString(this->main_menu_items_text[i]);
        this->main_menu_items.back().setFont(this->font);
        this->main_menu_items.back().setCharacterSize(40);
        this->main_menu_items.back().setFillColor(this->INACTIVE_TEXT_COLOR);
    }
}