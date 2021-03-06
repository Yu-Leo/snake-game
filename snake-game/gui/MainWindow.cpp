#include "MainWindow.h"

#include <iostream>

#include "../mechanics/SettingsKit.h"

MainWindow::MainWindow(const Size& size) : sf::RenderWindow(
    sf::VideoMode(size.width * CELL_SIZE, size.height * CELL_SIZE + TOP_PADDING),
    "Snake game",
    sf::Style::Close) {

    try {
        SettingsKit settings = SettingsKit::load_from_file();
        this->sounds.set_volume(settings.volume);
        this->speed.set_speed(settings.speed_item);
        this->map_number = settings.map_number;
    } catch (const std::exception& e) {
        // Settings file opening error. Do nothing
    }

    this->game_field_size = size;

    this->window_size.width = size.width * CELL_SIZE;
    this->window_size.height = size.height * CELL_SIZE + TOP_PADDING;

    this->game_field = GameField(size, map_number, true);

    this->load_textures();
    this->set_textures();

    this->set_text_settings();

    MenuList menu = MainWindow::MenuList();   
}

void MainWindow::event_handling() {
    sf::Event event;
    while (this->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->close();
        if (event.type == sf::Event::KeyPressed) { 
            switch (this->game_field.get_game_status()) {
            case GameField::GameStatus::ACTIVE: // Controlling
                this->handling_control(event);
                break;
            case GameField::GameStatus::STARTED: // Menu navigation
                if (this->menu.active != MenuList::SETTINGS)
                    this->menu.active = MenuList::MAIN;
                this->handling_menu_navigation(event);
                break;
            case GameField::GameStatus::FINISHED:
                if (this->menu.active != MenuList::SETTINGS)
                    this->menu.active = MenuList::MAIN;
                this->handling_menu_navigation(event);
                break;
            case GameField::GameStatus::PAUSE:
                if (this->menu.active != MenuList::SETTINGS)
                    this->menu.active = MenuList::PAUSE;
                this->handling_menu_navigation(event);
                break;
            }
        }

    }
}

void MainWindow::one_iteration() {
    if (game_field.get_game_status() == GameField::GameStatus::ACTIVE) {
        this->game_field.one_iteration();
        this->play_sounds();
        this->speed.update(*this);
    }
}

void MainWindow::redraw() {
    GameField::GameStatus game_status = this->game_field.get_game_status();
    switch (game_status) {
    case GameField::GameStatus::STARTED:
        this->draw_screen();
        this->menu.draw(*this);
        this->display();
        break;
    case GameField::GameStatus::ACTIVE:
        this->draw_screen();
        this->display();
        break;
    case GameField::GameStatus::PAUSE:
        this->draw_screen();
        this->menu.draw(*this);
        this->display();
        break;
    case GameField::GameStatus::FINISHED:
        this->menu.active = MenuList::MAIN;
        this->draw_screen();
        this->draw(this->game_over_text);
        this->display();
        sf::sleep(sf::seconds(1));
        this->game_field.start();
        break;
    }
}

void MainWindow::delay() {
    this->speed.delay();
}

void MainWindow::Speed::delay() {
    sf::sleep(sf::milliseconds(this->delays[this->speed]));
}

int MainWindow::Speed::get_num() const {
    return this->speed;
}

std::string MainWindow::Speed::get_active_item() const {
    return this->speed_items[this->active_speed_item];
}

void MainWindow::Speed::update(const MainWindow &window) {
    if (this->active_speed_item == 0) {
        this->auto_speed = true;
    } else {
        this->auto_speed = false;
        this->speed = this->active_speed_item - 1;
    }

    if (!this->auto_speed)
        return;

    int delays = this->delays.size();
    std::vector<double> borders = {
        0 * (1.0 / delays),
        1 * (1.0 / delays),
        2 * (1.0 / delays),
        3 * (1.0 / delays),
        4 * (1.0 / delays),
        5 * (1.0 / delays),
        6 * (1.0 / delays) };

    double k = 4 * double(window.game_field.get_score()) / window.game_field.get_cells_without_walls();
    if (borders[0] <= k && k < borders[1]) {
        this->speed = 0;
    } else if (borders[1] <= k && k < borders[2]) {
        this->speed = 1;
    } else if (borders[2] <= k && k < borders[3]) {
        this->speed = 2;
    } else if (borders[3] <= k && k < borders[4]) {
        this->speed = 3;
    } else if (borders[4] <= k && k < borders[5]) {
        this->speed = 4;
    } else if (borders[5] <= k) {
        this->speed = 5;
    }
}

void MainWindow::Speed::set_speed(std::string speed_item) {
    if (!this->is_correct_speed_item(speed_item))
        throw std::exception("Incorrect speed item");

    if (speed_item == this->speed_items[0]) {
        this->auto_speed = true;
        this->speed = 0;
        this->active_speed_item = 0;
    } else {
        this->auto_speed = false;
        this->speed = std::stoi(speed_item) - 1;
        this->active_speed_item = std::stoi(speed_item);
    }
}

void MainWindow::Speed::increase_speed() {
    this->active_speed_item++;
    if (this->active_speed_item >= this->speed_items.size())
        this->active_speed_item = 0;
}

void MainWindow::Speed::reduce_speed() {
    this->active_speed_item--;
    if (this->active_speed_item < 0)
        this->active_speed_item = this->speed_items.size() - 1;
}

bool MainWindow::Speed::is_correct_speed_item(std::string speed_item) {
    bool correct = false;
    for (auto item : this->speed_items)
        correct = correct || speed_item == item;
    return correct;
}



void MainWindow::load_textures() {
    this->textures.none.loadFromFile("./img/textures/none.png");
    this->textures.apple.loadFromFile("./img/textures/apple.png");
    this->textures.super_apple.loadFromFile("./img/textures/super_apple.png");
    this->textures.snake_body.loadFromFile("./img/textures/snake_body.png");
    this->textures.snake_head.loadFromFile("./img/textures/snake_head.png");
    this->textures.wall.loadFromFile("./img/textures/wall.png");
}

void MainWindow::set_textures() {
    this->sprites.none.setTexture(this->textures.none);
    this->sprites.apple.setTexture(this->textures.apple);
    this->sprites.super_apple.setTexture(this->textures.super_apple);
    this->sprites.snake_body.setTexture(this->textures.snake_body);
    this->sprites.snake_head.setTexture(this->textures.snake_head);
    this->sprites.wall.setTexture(this->textures.wall);
}

void MainWindow::set_text_settings() {
    this->font.loadFromFile("./fonts/pixel_font.ttf");

    this->score_text.setFont(this->font);
    this->score_text.setCharacterSize(35);
    this->score_text.setFillColor(sf::Color::White);

    this->game_over_text.setFont(this->font);
    this->game_over_text.setString("GAME OVER");
    this->game_over_text.setCharacterSize(120);
    this->game_over_text.setFillColor(sf::Color::White);
    this->game_over_text.setPosition(
        (this->window_size.width - this->game_over_text.getLocalBounds().width) / 2,
        (this->window_size.height - this->game_over_text.getLocalBounds().height) / 2);
}

void MainWindow::set_score_text_color() {
    sf::Color text_color;
    switch (this->speed.get_num()) {
    case 0:
        text_color = sf::Color::White;
        break;
    case 1:
        text_color = sf::Color(27, 245, 83); // Green
        break;
    case 2:
        text_color = sf::Color(215, 245, 81); // Yellow
        break;
    case 3:
        text_color = sf::Color(245, 81, 81); // Red
        break;
    case 4:
        text_color = sf::Color(77, 245, 225); // Blue
        break;
    case 5:
        text_color = sf::Color(245, 77, 214); // Purple
        break;
    default:
        break;
    }
    this->score_text.setFillColor(text_color);
}

void MainWindow::handling_control(const sf::Event& event) {
    this->game_field.key_pressed();
    switch (event.key.code) {
    case sf::Keyboard::Up:
        this->game_field.insert_command(Snake::Directions::UP);
        break;
    case sf::Keyboard::Right:
        this->game_field.insert_command(Snake::Directions::RIGHT);
        break;
    case sf::Keyboard::Down:
        this->game_field.insert_command(Snake::Directions::DOWN);
        break;
    case sf::Keyboard::Left:
        this->game_field.insert_command(Snake::Directions::LEFT);
        break;
    case sf::Keyboard::Escape:
        this->menu.active = MenuList::PAUSE;
        this->game_field.pause();
    }
}

void MainWindow::handling_menu_navigation(const sf::Event& event) {
    this->sounds.play(Sounds::MENU_NAVIGATE);
    switch (event.key.code) {
    case sf::Keyboard::Up:
        this->menu.previous_item();
        break;
    case sf::Keyboard::Down:
        this->menu.next_item();
        break;
    case sf::Keyboard::Left:
        if (this->menu.active == MenuList::SETTINGS) {
            switch (this->menu.settings.get_active_item_index()) {
            case 1:
                this->sounds.turn_down_volume();
                break;
            case 2:
                this->speed.reduce_speed();
                break;
            case 3:
                this->change_map(this->map_number - 1);
                break;
            }
        }
        break;
    case sf::Keyboard::Right:
        if (this->menu.active == MenuList::SETTINGS) {
            switch (this->menu.settings.get_active_item_index()) {
            case 1:
                this->sounds.turn_up_volume();
                break;
            case 2:
                this->speed.increase_speed();
                break;
            case 3:
                this->change_map(this->map_number + 1);
                break;
            }
        }
        break;
    case sf::Keyboard::Enter:
        this->menu.operations(*this);
        break;
    case sf::Keyboard::Escape:
        if (this->game_field.get_game_status() == GameField::GameStatus::PAUSE) {
            this->game_field.unpause();
            this->menu.active = MenuList::NONE;
            this->menu.reset_active_item();
        }
    }
}

void MainWindow::change_map(int new_map_num) {
    if (new_map_num < 0)
        new_map_num = MAPS.NUMBER_OF_MAPS - 1;
    else if (new_map_num > MAPS.NUMBER_OF_MAPS - 1)
        new_map_num = 0;

    this->map_number = new_map_num;
    this->game_field = GameField(game_field_size, new_map_num, true);
}


void MainWindow::play_sounds() {
    switch (this->game_field.get_collision()) {
    case GameField::Collisions::APPLE:
    case GameField::Collisions::SUPER_APPLE:
        this->sounds.play(Sounds::ATE_APPLE);
        break;
    case GameField::Collisions::BODY:
        this->sounds.play(Sounds::COLLISION_WITH_BODY);
        break;
    case GameField::Collisions::WALL:
        this->sounds.play(Sounds::COLLISION_WITH_WALL);
        break;
    }
    this->game_field.clear_collision();
}

void MainWindow::draw_screen() {
    this->clear(this->BACKGROUND_COLOR);
    this->draw_score_bar();
    this->draw_field();
}

void MainWindow::draw_field() {
    for (int i = 0; i < this->game_field.get_size().height; i++) {
        for (int j = 0; j < this->game_field.get_size().width; j++) {
            this->draw_cell(Point(j, i));
        }
    }
}

void MainWindow::draw_cell(const Point& point) {
    float x_pos = float(point.x * CELL_SIZE);
    float y_pos = float(point.y * CELL_SIZE + TOP_PADDING);
    float offset_x, offset_y;

    // Draw background dots
    this->sprites.none.setPosition(x_pos, y_pos);
    this->draw(this->sprites.none);

    switch (this->game_field.get_cell_type(point)) {
    case GameField::CellTypes::APPLE:
        this->sprites.apple.setPosition(x_pos, y_pos);
        this->draw(this->sprites.apple);
        break;

    case GameField::CellTypes::SUPER_APPLE:
        this->sprites.super_apple.setPosition(x_pos, y_pos);
        this->draw(this->sprites.super_apple);
        break;

    case GameField::CellTypes::SNAKE_BODY:
        this->sprites.snake_body.setPosition(x_pos, y_pos);
        this->draw(this->sprites.snake_body);
        break;

    case GameField::CellTypes::SNAKE_HEAD:
        offset_x = this->sprites.snake_head.getLocalBounds().width / 2;
        offset_y = this->sprites.snake_head.getLocalBounds().height / 2;
        this->sprites.snake_head.setPosition(x_pos + offset_x, y_pos + offset_y);
        this->sprites.snake_head.setOrigin(offset_x, offset_y);
        this->rotate_snake_head_sprite();
        this->draw(this->sprites.snake_head);
        break;

    case GameField::CellTypes::WALL:
        this->sprites.wall.setPosition(x_pos, y_pos);
        this->draw(this->sprites.wall);
        break;
    }
}

void MainWindow::rotate_snake_head_sprite() {
    int angle = 0;
    switch (this->game_field.get_snake_direction()) {
    case Snake::Directions::RIGHT:
        angle = 0;
        break;
    case Snake::Directions::DOWN:
        angle = 90;
        break;
    case Snake::Directions::LEFT:
        angle = 180;
        break;
    case Snake::Directions::UP:
        angle = -90;
        break;
    }
    this->sprites.snake_head.setRotation(angle);
}

void MainWindow::draw_score_bar() {
    this->set_score_text_color();
    this->score_text.setString("Score: " + std::to_string(this->game_field.get_score()));
    this->score_text.setPosition(
        this->window_size.width - this->score_text.getLocalBounds().width - 20, 7);
    this->draw(this->score_text);
}



MainWindow::MenuList::MenuList() {
    std::vector<std::string> main_menu_items = { "Start new game", "Settings", "Quit" };
    std::vector<std::string> pause_menu_items = { "Resume game", "Settings", "Quit" };
    std::vector<std::string> settings_menu_items = { "Back to main menu", "Volume: ", "Speed: ", "Map: " };

    this->main.set_text_to_items(main_menu_items);
    this->pause.set_text_to_items(pause_menu_items);
    this->settings.set_text_to_items(settings_menu_items);
}

void MainWindow::MenuList::draw(MainWindow& window) {
    switch (this->active) {
    case MenuList::MAIN:
        this->main.draw(window);
        break;
    case MenuList::PAUSE:
        this->pause.draw(window);
        break;
    case MenuList::SETTINGS:
        int volume = window.sounds.get_volume();
        int map_num = window.map_number;
        this->settings.set_text_to_item(1, "Volume: " + std::to_string(volume));
        this->settings.set_text_to_item(2, "Speed: " + window.speed.get_active_item());
        this->settings.set_text_to_item(3, "Map: " + std::to_string(map_num));
        this->settings.draw(window);
        break;
    }
}

void MainWindow::MenuList::operations(MainWindow& window) {
    switch (this->active) {
    case ActiveMenu::MAIN:
        this->main_menu_operations(window);
        break;

    case ActiveMenu::PAUSE:
        this->pause_menu_operations(window);
        break;

    case ActiveMenu::SETTINGS:
        this->settings_menu_operations(window);
        break;
    }
}

void MainWindow::MenuList::next_item() {
    switch (this->active) {
    case ActiveMenu::MAIN:
        this->main.next_item();
        break;

    case ActiveMenu::PAUSE:
        this->pause.next_item();
        break;

    case ActiveMenu::SETTINGS:
        this->settings.next_item();
        break;
    }

}

void MainWindow::MenuList::previous_item() {
    switch (this->active) {
    case ActiveMenu::MAIN:
        this->main.previous_item();
        break;
    case ActiveMenu::PAUSE:
        this->pause.previous_item();
        break;
    case ActiveMenu::SETTINGS:
        this->settings.previous_item();
        break;
    }
}

void MainWindow::MenuList::reset_active_item() {
    this->main.reset_active_item();
    this->pause.reset_active_item();
    this->settings.reset_active_item();
}

void MainWindow::MenuList::main_menu_operations(MainWindow& window) {
    switch (this->main.get_active_item_index()) {
    case 0: // First item
        window.game_field = GameField(window.game_field_size, window.map_number);
        window.game_field.unpause();
        break;
    case 1: // Second item
        this->active = ActiveMenu::SETTINGS;
        break;
    case 2: // Third item
        SettingsKit current_settings(
            window.sounds.get_volume(),
            window.speed.get_active_item(),
            window.map_number);
        current_settings.save_to_file();
        window.close();
        break;
    }
}

void MainWindow::MenuList::pause_menu_operations(MainWindow& window) {
    switch (this->pause.get_active_item_index()) {
    case 0: // First item
        window.game_field.unpause();
        break;
    case 1: // Second item
        this->active = ActiveMenu::SETTINGS;
        break;
    case 2: // Third item
        SettingsKit current_settings(
            window.sounds.get_volume(),
            window.speed.get_active_item(),
            window.map_number);
        current_settings.save_to_file();
        window.close();
        break;
    }
}

void MainWindow::MenuList::settings_menu_operations(MainWindow& window) {
    switch (this->settings.get_active_item_index()) {
    case 0: // First item
        if (window.game_field.get_game_status() == GameField::GameStatus::PAUSE)
            this->active = PAUSE;
        else
            this->active = MAIN;
        break;
    }
}

