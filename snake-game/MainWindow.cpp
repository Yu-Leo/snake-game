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
        if (event.type == sf::Event::KeyPressed) { 
            switch (this->game_field.get_game_status()) {
                case GameField::GameStatus::ON: // Controlling
                    this->handling_control(event);
                    break;

                case GameField::GameStatus::PAUSE: // Menu navigation
                    this->handling_menu_navigation(event);
                    break;
            }
        }

    }
}

void MainWindow::handling_control(const sf::Event &event) {
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
            this->game_field.pause();
    }
}

void MainWindow::handling_menu_navigation(const sf::Event &event) {
    switch (event.key.code) {
        case sf::Keyboard::Up:
            this->menu.previous_item();
            break;
        case sf::Keyboard::Down:
            this->menu.next_item();
            break;
        case sf::Keyboard::Enter:
            this->main_menu_operations();
            break;
        case sf::Keyboard::Escape:
            this->game_field.unpause();

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
        this->menu.draw_main_menu(*this);
        this->display();
    } else if (game_status == GameField::GameStatus::OFF) {
        this->draw_screen();
        this->draw(this->game_over_text);
        this->display();
        sf::sleep(sf::seconds(1));

        this->game_field.pause();
        this->menu.draw_main_menu(*this);
        
        //this->close();
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

void MainWindow::main_menu_operations() {
    switch (this->menu.get_active_item_index()) {
        case 0: // First item
            this->game_field.unpause();
            break;
        case 1: // Second item
            break;
        case 2: // Third item
            this->close();
            break;
    }
}