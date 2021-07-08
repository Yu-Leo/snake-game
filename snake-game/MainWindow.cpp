#include "MainWindow.h"

MainWindow::MainWindow(const Size& size) : sf::RenderWindow(
    sf::VideoMode(size.width * CELL_SIZE, size.height * CELL_SIZE + TOP_PADDING),
    "Snake game",
    sf::Style::Close) {

    this->size.width = size.width * CELL_SIZE;
    this->size.height = size.height * CELL_SIZE + TOP_PADDING;

    this->game_field = GameField(size);

    this->load_textures();
    this->set_textures();

    this->set_text_settings();

}

void MainWindow::event_handling() {
    sf::Event event;
    while (this->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->close();
        if (event.type == sf::Event::KeyPressed) { // Controlling
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
                if (game_field.get_game_status() == GameField::GameStatus::ON) {
                    this->game_field.pause();
                } else {
                    this->game_field.unpause();
                }
            default:
                break;
            }
        }
    }
}

void MainWindow::one_iteration() {
    if (game_field.get_game_status() == GameField::GameStatus::ON) {
        this->game_field.one_iteration();
        this->play_sounds();
    }
}

void MainWindow::redraw() {
    GameField::GameStatus game_status = this->game_field.get_game_status();
    if (game_status == GameField::GameStatus::ON) {
        this->draw_screen();
        this->display();
    } else if (game_status == GameField::GameStatus::PAUSE) {
        this->draw_screen();
        this->draw_menu();
        this->display();
    } else if (game_status == GameField::GameStatus::OFF) {
        this->draw_screen();
        this->draw(this->game_over_text);
        this->display();
        sf::sleep(sf::seconds(1));
        
        this->close();
    }
}

void MainWindow::delay() {
    int ms[] = { 150, 130, 110, 90, 70 };
    sf::sleep(sf::milliseconds(ms[this->speed]));
}

void MainWindow::load_textures() {
    this->textures.none.loadFromFile("./img/textures/none.png");
    this->textures.apple.loadFromFile("./img/textures/apple.png");
    this->textures.snake.loadFromFile("./img/textures/snake.png");
    this->textures.wall.loadFromFile("./img/textures/wall.png");
}

void MainWindow::set_textures() {
    this->sprites.none.setTexture(this->textures.none);
    this->sprites.apple.setTexture(this->textures.apple);
    this->sprites.snake.setTexture(this->textures.snake);
    this->sprites.wall.setTexture(this->textures.wall);
}

void MainWindow::set_text_settings() {
    this->font.loadFromFile("./fonts/pixel_font.ttf");
    this->menu_font.loadFromFile("./fonts/menu_font.ttf");

    this->score_text.setFont(this->font);
    this->score_text.setCharacterSize(35);
    this->score_text.setFillColor(sf::Color::White);

    this->game_over_text.setFont(this->font);
    this->game_over_text.setString("GAME OVER");
    this->game_over_text.setCharacterSize(120);
    this->game_over_text.setFillColor(sf::Color::White);
    this->game_over_text.setPosition(
        (this->size.width - this->game_over_text.getLocalBounds().width) / 2,
        (this->size.height - this->game_over_text.getLocalBounds().height) / 2);

    for (int i = 0; i < this->main_menu_items_text.size(); i++) {
        this->main_menu_items.push_back(sf::Text());
        this->main_menu_items.back().setString(this->main_menu_items_text[i]);
        this->main_menu_items.back().setFont(this->menu_font);
        //this->main_menu_items.back().setFont(this->font);
        this->main_menu_items.back().setCharacterSize(40);
        this->main_menu_items.back().setFillColor(sf::Color::Black);
    }
}

void MainWindow::play_sounds() {
    switch (this->game_field.get_collision()) {
    case GameField::Collisions::APPLE:
        this->sounds.play(Sounds::ATE_APPLE);
        break;
    case GameField::Collisions::BODY:
        this->sounds.play(Sounds::COLLISION_WITH_BODY);
        break;
    case GameField::Collisions::WALL:
        this->sounds.play(Sounds::COLLISION_WITH_WALL);
        break;
    default:
        break;
    }
    this->game_field.clear_collision();
}

void MainWindow::draw_cell(const Point& point) {
    float x_pos = float(point.x * CELL_SIZE);
    float y_pos = float(point.y * CELL_SIZE + TOP_PADDING);
    switch (this->game_field.get_cell_type(point)) {
    case GameField::CellTypes::NONE:
        this->sprites.none.setPosition(x_pos, y_pos);
        this->draw(this->sprites.none);
        break;

    case GameField::CellTypes::APPLE:
        this->sprites.apple.setPosition(x_pos, y_pos);
        this->draw(this->sprites.apple);
        break;

    case GameField::CellTypes::SNAKE:
        this->sprites.snake.setPosition(x_pos, y_pos);
        this->draw(this->sprites.snake);
        break;

    case GameField::CellTypes::WALL:
        this->sprites.wall.setPosition(x_pos, y_pos);
        this->draw(this->sprites.wall);
        break;
    }
}

void MainWindow::draw_field() {
    for (int i = 0; i < this->game_field.get_size().height; i++) {
        for (int j = 0; j < this->game_field.get_size().width; j++) {
            this->draw_cell(Point(j, i));
        }
    }
}

void MainWindow::draw_score_bar() {
    this->score_text.setString("Score: " + std::to_string(this->game_field.get_score()));
    this->score_text.setPosition(
        this->size.width - this->score_text.getLocalBounds().width - 20, 7);
    this->draw(this->score_text);
}

void MainWindow::draw_screen() {
    this->clear(this->BACKGROUND_COLOR);
    this->draw_score_bar();
    this->draw_field();
}

void MainWindow::draw_menu() {
    const float menu_item_interval = 20;

    float current_munu_item_y = 0;
    float menu_item_max_width = 0;

    for (int i = 0; i < this->main_menu_items.size(); i++) {
        this->main_menu_items[i].setPosition(0, current_munu_item_y);
        current_munu_item_y += this->main_menu_items[i].getLocalBounds().height + menu_item_interval;
        menu_item_max_width = std::max(menu_item_max_width, this->main_menu_items[i].getLocalBounds().width);
    }
    const Size menu(menu_item_max_width, current_munu_item_y);

    const int menu_pos_x = (this->size.width - menu.width) / 2;
    const int menu_pos_y = (this->size.height - menu.height) / 2;

    sf::RectangleShape menu_rect(sf::Vector2f(menu.width, menu.height));
    menu_rect.setPosition(menu_pos_x, menu_pos_y);
    menu_rect.setFillColor(sf::Color(255, 255, 255, 220));
    this->draw(menu_rect);

    for (int i = 0; i < this->main_menu_items.size(); i++) {
        this->main_menu_items[i].move(menu_pos_x, menu_pos_y);
        this->draw(this->main_menu_items[i]);
    }

}