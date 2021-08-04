#include "Menu.h"

Menu::Menu() {
    this->load_font();
}

void Menu::set_text_to_items(const std::vector<std::string>& titles) {
    this->set_titles(titles);
    this->set_font_settings();
}

void Menu::set_text_to_item(int index, const std::string& text) {
    this->menu_items[index].setString(text);
}

void Menu::draw(sf::RenderWindow& window) {
    Size background_size = this->get_background_size();
    Position background_pos((window.getSize().x - background_size.width) / 2,
        (window.getSize().y - background_size.height) / 2);

    this->draw_background(window, background_size, background_pos);

    this->draw_items(window, background_pos);
}

void Menu::next_item() {
    this->active_item_index += 1;
    this->active_item_index %= this->menu_items.size();
}

void Menu::previous_item() {
    this->active_item_index -= 1;
    if (this->active_item_index < 0) {
        this->active_item_index = this->menu_items.size() - 1;
    }
}

void Menu::reset_active_item() {
    this->active_item_index = 0;
}

int Menu::get_active_item_index() {
    return this->active_item_index;
}

void Menu::load_font() {
    this->font.loadFromFile("./fonts/menu_font.ttf");
}

void Menu::set_font_settings() {
    for (unsigned int i = 0; i < this->menu_items.size(); i++) {
        this->menu_items[i].setFont(this->font);
        this->menu_items[i].setCharacterSize(40);
        this->menu_items[i].setFillColor(this->INACTIVE_TEXT_COLOR);
    }
}

void Menu::set_titles(const std::vector<std::string>& titles) {
    for (unsigned int i = 0; i < titles.size(); i++) {
        this->menu_items.push_back(sf::Text());
        this->menu_items.back().setString(titles[i]);
    }
}

void Menu::draw_background(sf::RenderWindow& window, const Size& size, const Position& pos) {
    sf::RectangleShape menu_rect(sf::Vector2f(size.width, size.height));
    menu_rect.setPosition(pos.x, pos.y);
    menu_rect.setFillColor(this->BACKGROUND_COLOR);
    window.draw(menu_rect);
}

void Menu::draw_items(sf::RenderWindow& window, const Position& bg_pos) {
    float current_y_pos = 0.0;
    for (unsigned int i = 0; i < this->menu_items.size(); i++) {
        sf::Color fill_color = (this->active_item_index == i ?
            this->ACTIVE_TEXT_COLOR : this->INACTIVE_TEXT_COLOR);

        this->menu_items[i].setFillColor(fill_color);

        this->menu_items[i].setPosition(bg_pos.x + this->HORIZONTAL_PADDING,
            bg_pos.y + this->VERTICAL_PADDING + current_y_pos);

        current_y_pos += this->menu_items[i].getLocalBounds().height +
            this->ITEM_PADDING;

        window.draw(this->menu_items[i]);
    }
}

Size Menu::get_background_size() {
    float current_menu_item_y = 0;
    float menu_item_max_width = 0;

    for (unsigned int i = 0; i < this->menu_items.size(); i++) {
        current_menu_item_y += this->menu_items[i].getLocalBounds().height + this->ITEM_PADDING;
        menu_item_max_width = std::max(menu_item_max_width, this->menu_items[i].getLocalBounds().width);
    }

    return Size(menu_item_max_width + this->HORIZONTAL_PADDING * 2,
        current_menu_item_y - this->ITEM_PADDING + this->VERTICAL_PADDING * 2);
}