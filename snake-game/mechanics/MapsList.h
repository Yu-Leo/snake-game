#pragma once

#include <vector>
#include "Map.h"

class MapsList {
public:
    const int NUMBER_OF_MAPS = 5;

    MapsList(const Size &size) {
        this->maps.resize(this->NUMBER_OF_MAPS);

        for (int i = 0; i < NUMBER_OF_MAPS; i++)
            this->maps[i] = Map::read_from_file("map" + std::to_string(i) + ".txt");
    }

    Map operator[](int index) const {
        if (index < 0 || index >= NUMBER_OF_MAPS)
            throw false;
        return this->maps[index];
    }

private:
    std::vector<Map> maps;
};

