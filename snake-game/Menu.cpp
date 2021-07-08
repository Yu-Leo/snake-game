#include "Menu.h"

#include "Size.h"

void Menu::draw_main_menu(sf::RenderWindow& window) {
    const float menu_item_interval = 20;

    float current_munu_item_y = 0;
    float menu_item_max_width = 0;

    for (int i = 0; i < this->main_menu_items.size(); i++) {
        this->main_menu_items[i].setPosition(0, current_munu_item_y);
        current_munu_item_y += this->main_menu_items[i].getLocalBounds().height + menu_item_interval;
        menu_item_max_width = std::max(menu_item_max_width, this->main_menu_items[i].getLocalBounds().width);
    }

    const Size menu(menu_item_max_width, current_munu_item_y);

    const int menu_pos_x = (window.getSize().x - menu.width) / 2;
    const int menu_pos_y = (window.getSize().y - menu.height) / 2;

    sf::RectangleShape menu_rect(sf::Vector2f(menu.width, menu.height));
    menu_rect.setPosition(menu_pos_x, menu_pos_y);
    menu_rect.setFillColor(sf::Color(255, 255, 255, 220));
    window.draw(menu_rect);

    for (int i = 0; i < this->main_menu_items.size(); i++) {
        this->main_menu_items[i].move(menu_pos_x, menu_pos_y);
        window.draw(this->main_menu_items[i]);
    }

}

void Menu::set_font_settings() {
    this->font.loadFromFile("./fonts/menu_font.ttf");

    for (int i = 0; i < this->main_menu_items_text.size(); i++) {
        this->main_menu_items.push_back(sf::Text());
        this->main_menu_items.back().setString(this->main_menu_items_text[i]);
        this->main_menu_items.back().setFont(this->font);
        this->main_menu_items.back().setCharacterSize(40);
        this->main_menu_items.back().setFillColor(sf::Color::Black);
    }
}