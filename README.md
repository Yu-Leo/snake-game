# Snake game

## Навигация

* [Описание проекта](#chapter-0)
* [Как начать](#chapter-1)
* [Интерфейс](#chapter-2)
* [Код](#chapter-3)
* [Лицензия](#chapter-4)

<a id="chapter-0"></a>

## :page_facing_up: Описание проекта

Классическая игра "Змейка".


Игрок управляет длинным, тонким существом, напоминающим змею, которое ползает по плоскости, собирая яблоки и избегая столкновения с собственным хвостом и стенами. Каждый раз, когда змейка съедает яблоко, она становится длиннее, что постепенно усложняет игру. Игра заканчивается, когда голова змейки сталкивается с хвостом змейки или врезается в стену.


В игре присутствует 2 вида яблок: красные и желтые. Съедание красного яблока увеличивает длину змейки на одну клетку, а съедание желтого – на две.

<a id="chapter-1"></a>

## :hammer: Как начать

1. Установить [Visual Studio 2019](https://visualstudio.microsoft.com/ru/downloads/)
2. Скачать [SFML](https://www.sfml-dev.org/download.php)
3. Скачать данный репозиторий
   * Вариант 1
      1. Установить [Git](https://git-scm.com/download/win)
      2. Клонировать репозиторий
      ```bash
      git clone https://github.com/Yu-Leo/snake-game.git
      cd snake-game
      ```
   * Вариант 2 - [Скачать ZIP](https://github.com/Yu-Leo/snake-game/archive/refs/heads/master.zip)
4. Подключить SFML к проекту ([как это сделать](https://www.sfml-dev.org/tutorials/2.5/start-vc.php))
5. Скомпилировать и запустить `./snake-game/main.cpp`

<a id="chapter-2"></a>

## :camera: Интерфейс

### Меню

Навигация по меню осуществляется при помощи *стрелок вверх и вниз*. Выбор пункта меню – *Enter*. Изменение значений в настройках – *стрелками влево и вправо*.


#### :bookmark_tabs: Главное меню
![main_menu](./docs/img/main-menu.jpg)

* **Start new game** - начать новую игру.
* **Settings** - переход в меню настроек.
* **Quit** - выход из игры.


#### :bookmark_tabs: Меню паузы
![pause_menu](./docs/img/pause-menu.jpg)

* **Resume new game** - возобновить игру.
* **Settings** - переход в меню настроек.
* **Quit** - выход из игры.


#### :wrench: Меню настроек

![settings](./docs/img/settings-menu.jpg)

* **Back to main menu** - вернуться в главное меню.
* **Volume** - уровень громкости. От 0 до 100. Регулировка происходит при помощи стрелок влево (уменьшить на 5) и вправо (увеличить на 5).

### :video_game: Игровое поле

![game field](./docs/img/game-field.jpg)

![snake-body-cell](./snake-game/img/textures/snake_body.png) - тело змейки

![snake-head-cell](./snake-game/img/textures/snake_head.png) - голова змейки

![apple-cell](./snake-game/img/textures/apple.png) - яблоко

![super-apple-cell](./snake-game/img/textures/super_apple.png) - супер яблоко

![wall-cell](./snake-game/img/textures/wall.png) - стена


Управление происходит при помощи *стрелок вверх, вниз, вправо, и влево* на клавиатуре. При нажатии *Escape* во время игры активируется пауза и открывается меню паузы. При нажатии *Escape* в режиме паузы игра продолжается.

В случае проигрыша выводится надпись "Game over", после чего происходит переход в главное меню игры

![game over](./docs/img/game-over.jpg)


<a id="chapter-3"></a>

## :computer: Код

[Техническая документация](./docs/technical-documentation.pdf)

### :file_folder: Папки
**snake-game** - исходный код проекта.

**tests** - unit-тесты.

### :wrench: Настройки


1. Генерация яблок в случайных (`true`) или псевдо-случайных (`false`) местах
```cpp
// main.cpp

#define RANDOM_GENERATING false
```

При установке `false` стартовое значение для псевдо-случайной генерации задаётся в строчке
```cpp
// main.cpp

    srand(0); // Set seed for pseudorandom number generator
```

2. Шанс генерации супер-яблока (в процентах)

```cpp
// GameField.h

#define CHANCE_OF_GENERATING_SUPER_APPLE 15
```

### :coffee: Тесты

Запуск:

![tests](./docs/img/tests.jpg)


<a id="chapter-4"></a>

## :open_hands: Лицензия
Автор: [Yu-Leo](https://github.com/Yu-Leo)

GNU General Public License v3.0.

Полный текст в [LICENSE](LICENSE)
