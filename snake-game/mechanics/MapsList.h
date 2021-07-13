#pragma once

#include <vector>
#include "Map.h"

class MapsList {
public:
    const int NUMBER_OF_MAPS = 2;

    MapsList(const Size &size) {
        this->maps.resize(this->NUMBER_OF_MAPS);

        this->maps[0] = Map(size);
        this->maps[1] = Map(size, borders(size));
    }
    
    Map get_map(int index) const;

private:
    std::vector<Map> maps;

    std::vector<std::vector<int>> borders(const Size& size);
};

