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
    
    this->load_sound_buffers();
    this->set_sound_buffers();

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
                this->game_field.finish_game();
            default:
                break;
            }
        }
    }
}

void MainWindow::one_iteration() {
    this->game_field.one_iteration();
    this->play_sounds();
}

void MainWindow::redraw() {
    GameField::GameStatus game_status = this->game_field.get_game_status();
    if (game_status == GameField::GameStatus::ON) {
        this->clear(sf::Color(0, 0, 0));
        this->draw_score_bar();
        this->draw_field();
        this->display();
    } else if (game_status == GameField::GameStatus::OFF) {
        this->draw(this->game_over_text);
        this->display();
        sf::sleep(sf::seconds(2));
        
        this->close();
    }
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

void MainWindow::load_sound_buffers() {
    this->sound_buffers.ate_apple.loadFromFile("./sounds/ate_apple.wav");
    this->sound_buffers.collision_with_wall.loadFromFile("./sounds/collision_with_wall.wav");
    this->sound_buffers.collision_with_body.loadFromFile("./sounds/collision_with_body.wav");
}

void MainWindow::set_sound_buffers() {
    this->sounds.ate_apple.setBuffer(this->sound_buffers.ate_apple);
    this->sounds.collision_with_wall.setBuffer(this->sound_buffers.collision_with_wall);
    this->sounds.collision_with_body.setBuffer(this->sound_buffers.collision_with_body);
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
        this->sounds.ate_apple.play();
        break;
    case GameField::Collisions::BODY:
        this->sounds.collision_with_body.play();
        break;
    case GameField::Collisions::WALL:
        this->sounds.collision_with_wall.play();
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