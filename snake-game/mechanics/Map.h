#pragma once

#include <vector>
#include <string>

#include "Size.h"

struct Map {
    static const int WALL = 1;
    static const int NONE = 0;

    std::vector<std::vector<int>> map;
    Size size;

    Map(const Size& size = Size(), const std::vector<std::vector<int>>& map = {}) {
        this->size = size;
        if (map.size() == 0) {
            this->map.resize(size.height);
            for (int i = 0; i < size.height; i++)
                this->map[i].resize(size.width, NONE);
        } else {
            this->map = map;
        }
    }

    static Map read_from_file(const std::string& file_name);
};
