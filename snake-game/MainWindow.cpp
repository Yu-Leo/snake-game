#include "MainWindow.h"

MainWindow::MainWindow(const Size& size) : sf::RenderWindow(
    sf::VideoMode(size.width * CELL_SIZE, size.height * CELL_SIZE),
    "Snake game",
    sf::Style::Close) {

    this->game_field = GameField(size);
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
    if (this->game_field.get_game_status()) {
        this->draw_field();
        this->display();
    } else {
        this->close();
    }
}

void MainWindow::draw_cell(const Point& point, sf::RectangleShape& cell) {
    cell.setPosition(float(point.x * CELL_SIZE), float(point.y * CELL_SIZE));
    switch (this->game_field.get_cell_at(point)) {
    case GameField::FIELD_CELL_TYPE_NONE:
        cell.setFillColor(sf::Color::Black);
        break;
    case GameField::FIELD_CELL_TYPE_APPLE:
        cell.setFillColor(sf::Color::Red);
        break;
    default:
        cell.setFillColor(sf::Color::Green);
        break;
    }
    this->draw(cell);
}

void MainWindow::draw_field() {
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (int i = 0; i < this->game_field.get_size().height; i++) {
        for (int j = 0; j < this->game_field.get_size().width; j++) {
            this->draw_cell(Point(j, i), cell);
        }
    }
}