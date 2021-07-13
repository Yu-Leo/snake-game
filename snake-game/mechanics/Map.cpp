#include "Map.h"

#include <fstream>

Map Map::read_from_file(const std::string& file_name) {
	Map map;
	std::string path = "./maps/" + file_name;
	std::ifstream fin;
	fin.open(path);
	int w, h;
	fin >> w >> h;
	map = Map(Size(w, h));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int cell;
			fin >> cell;
			if (cell == Map::NONE || cell == Map::WALL) {
				map.map[i][j] = cell;
			} else {
				throw false;
			}
		}
	}
	fin.close();
	return map;
}