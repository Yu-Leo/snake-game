#include "MapsList.h"

Map MapsList::get_map(int index) const {
    return this->maps[index];
}

std::vector<std::vector<int>> MapsList::borders(const Size& size) {
    std::vector<std::vector<int>> map(size.height, std::vector<int>(size.width));
    for (int i = 0; i < size.width; i++) {
        map[size.height - 1][i] = Map::WALL;
    }

    for (int i = 0; i < size.width; i++) {
        map[0][i] = Map::WALL;
    }

    for (int i = 0; i < size.height; i++) {
        map[i][0] = Map::WALL;
    }

    for (int i = 0; i < size.height; i++) {
        map[i][size.width - 1] = Map::WALL;
    }
    return map;
}
