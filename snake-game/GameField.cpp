#include "GameField.h"

GameField::GameField(const Size& size) {
    this->size = size;
    this->init_field();

    this->set_walls();

    // Create snake
    this->snake.set_field_size(this->size);
    this->render_snake();

    // Create apple
    this->apple = Apple(this->get_random_empty_cell());
    this->render_apple();

    this->cells_without_walls = this->count_cells_without_walls();

    this->game_status = GameField::GameStatus::STARTED;
}

GameField::GameField() : GameField(Size(20, 20)) {}

void GameField::one_iteration() {
    this->turn_snake(); // Analyze queue of controlling commands
    this->move_snake();
}

void GameField::key_pressed() {
    this->last_snake_direction = (this->snake_directions.empty() ?
        this->snake.get_direction() : this->snake_directions.front());
}

void GameField::insert_command(int direction) {
    if (this->snake_directions.size() >= 3) {
        return;
    }

    switch (direction) {
    case Snake::Directions::UP:
        if (this->last_snake_direction != Snake::Directions::DOWN) {
            this->snake_directions.push(Snake::Directions::UP);
        }
        break;

    case Snake::Directions::RIGHT:
        if (this->last_snake_direction != Snake::Directions::LEFT) {
            this->snake_directions.push(Snake::Directions::RIGHT);
        }
        break;

    case Snake::Directions::DOWN:
        if (this->last_snake_direction != Snake::Directions::UP) {
            this->snake_directions.push(Snake::Directions::DOWN);
        }
        break;

    case Snake::Directions::LEFT:
        if (this->last_snake_direction != Snake::Directions::RIGHT) {
            this->snake_directions.push(Snake::Directions::LEFT);
        }
        break;

    default:
        break;
    }
}

void GameField::start() {
    this->game_status = GameStatus::STARTED;
}

void GameField::finish() {
    this->game_status = GameStatus::FINISHED;
}

void GameField::pause() {
    this->game_status = GameStatus::PAUSE;
}

void GameField::unpause() {
    this->game_status = GameStatus::ACTIVE;
}

int GameField::get_score() const {
    return this->score;
}

Size GameField::get_size() const {
    return this->size;
}

int GameField::get_cells_without_walls() const{
    return this->cells_without_walls;
}

GameField::GameStatus GameField::get_game_status() const{
    return this->game_status;
}

GameField::CellTypes GameField::get_cell_type(const Point& point) const {
    switch (this->field[point.y][point.x]) {
    case this->FIELD_CELL_TYPE_NONE:
        return CellTypes::NONE;
    case this->FIELD_CELL_TYPE_APPLE:
        return CellTypes::APPLE;
    case this->FIELD_CELL_TYPE_WALL:
        return CellTypes::WALL;
    default:
        return CellTypes::SNAKE;
    }
}

GameField::Collisions GameField::get_collision() const {
    return this->collision;
}

void GameField::clear_collision() {
    this->collision = Collisions::NONE;
}


void GameField::resize_matrix() {
    this->field.resize(this->size.height);
    for (int i = 0; i < this->size.height; i++) {
        this->field[i].resize(this->size.width);
    }
}

void GameField::init_field() {
    this->resize_matrix();
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            this->field[i][j] = this->FIELD_CELL_TYPE_NONE;
        }
    }
}

void GameField::move_snake() {
    this->snake.move_head();

    this->check_collisions();
    if (this->game_status == GameStatus::FINISHED)
        return;

    this->decrease_snake_cells();
    Point hp = this->snake.get_head_pos();
    this->field[hp.y][hp.x] = this->snake.get_length();
}

void GameField::turn_snake() {
    if (!this->snake_directions.empty()) {
        this->snake.change_direction(this->snake_directions.front());
        this->snake_directions.pop();
    }
}

void GameField::check_collisions() {
    Point hp = this->snake.get_head_pos();
    if (this->field[hp.y][hp.x] == this->FIELD_CELL_TYPE_NONE)
        return;
    switch (this->field[hp.y][hp.x]) {
        case FIELD_CELL_TYPE_APPLE:
            this->score++;
            this->snake.increase_length();
            this->grow_snake();
            this->apple = Apple(this->get_random_empty_cell());
            this->render_apple();
            this->collision = Collisions::APPLE;
            break;
        case FIELD_CELL_TYPE_WALL:
            this->finish();
            this->collision = Collisions::WALL;
        default:
            if (this->field[hp.y][hp.x] > 1) {
                this->finish();
                this->collision = Collisions::BODY;
            }
            break;
    }
}

void GameField::grow_snake() {
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] > FIELD_CELL_TYPE_NONE) {
                this->field[i][j]++;
            }
        }
    }
}

void GameField::decrease_snake_cells() {
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] > this->FIELD_CELL_TYPE_NONE) {
                this->field[i][j]--;
            }
        }
    }
}

void GameField::set_walls() {
    for (int i = 0; i < this->size.width; i++) {
        this->field[this->size.height - 1][i] = FIELD_CELL_TYPE_WALL;
    }

    for (int i = 0; i < this->size.width; i++) {
        this->field[0][i] = FIELD_CELL_TYPE_WALL;
    }

    for (int i = 0; i < this->size.height; i++) {
        this->field[i][0] = FIELD_CELL_TYPE_WALL;
    }

    for (int i = 0; i < this->size.height; i++) {
        this->field[i][this->size.width - 1] = FIELD_CELL_TYPE_WALL;
    }
}

void GameField::render_snake() {
    int snake_len = this->snake.get_length();
    for (int i = 0; i < snake_len; i++) {
        Point hp = this->snake.get_head_pos();
        this->field[hp.y][hp.x - i] = snake_len - i;
    }
}

void GameField::render_apple() {
    Point dot = this->apple.get_coordinates();
    this->field[dot.y][dot.x] = this->FIELD_CELL_TYPE_APPLE;
}

bool GameField::is_cell_empty(const Point& cell) {
    return this->field[cell.y][cell.x] == this->FIELD_CELL_TYPE_NONE;
}

int GameField::count_empty_cells() {
    int count = 0;
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            count += int(this->is_cell_empty(Point(j, i)));
        }
    }
    return count;
}

Point GameField::get_random_empty_cell() {
    int empty_cells = this->count_empty_cells();
    int target_empty_cell_index = rand() % empty_cells;
    int empty_cell_index = 0;
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] == FIELD_CELL_TYPE_NONE) {
                if (empty_cell_index == target_empty_cell_index) {
                    return Point(j, i);
                }
                empty_cell_index++;
            }
        }
    }
    throw std::exception("No empty cells");
}

int GameField::count_cells_without_walls() {
    int walls = 0;
    for (int i = 0; i < this->size.height; i++) {
        for (int j = 0; j < this->size.width; j++) {
            if (this->field[i][j] == this->FIELD_CELL_TYPE_WALL)
                walls++;
        }
    }
    return this->size.height * this->size.width - walls;
}

void print_cell(std::ostream& out, const GameField& game_field, const Point &cell) {
    switch (game_field.get_cell_type(cell)) {
        case GameField::CellTypes::NONE:
            out << (char)GameField::Symbols::NONE;
            break;
        case GameField::CellTypes::APPLE:
            out << (char)GameField::Symbols::APPLE;
            break;
        case GameField::CellTypes::WALL:
            out << (char)GameField::Symbols::WALL;
            break;
        case GameField::CellTypes::SNAKE:
            out << (char)GameField::Symbols::SNAKE;
            break;
    }
}

std::ostream& operator<<(std::ostream& out, const GameField& game_field) {
    for (int i = 0; i < game_field.size.height; i++) {
        for (int j = 0; j < game_field.size.width; j++) {
            print_cell(out, game_field, Point(j, i));
            out << ' ';
        }
        out << '\n';
    }
    return out;
}