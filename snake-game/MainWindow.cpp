#include "MainWindow.h"

MainWindow::MainWindow(const Size& size) : sf::RenderWindow(
    sf::VideoMode(size.width * CELL_SIZE, size.height * CELL_SIZE),
    "Snake game",
    sf::Style::Close) {

    this->game_field = GameField(size);

    this->load_textures();
    this->set_textures();
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
}

void MainWindow::redraw() {
    GameField::GameStatus game_status = this->game_field.get_game_status();
    if (game_status == GameField::GameStatus::ON) {
        this->clear(sf::Color(0, 0, 0));
        this->draw_field();
        this->display();
    } else if (game_status == GameField::GameStatus::OFF) {
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

void MainWindow::draw_cell(const Point& point) {
    float x_pos = float(point.x * CELL_SIZE);
    float y_pos = float(point.y * CELL_SIZE);
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