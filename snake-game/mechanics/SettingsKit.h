#pragma once
#include <string>

const std::string FILE_NAME = "settings.txt";

struct SettingsKit {

	int volume;
	std::string speed_item;
	int map_number;

	SettingsKit();

	SettingsKit(int volume, std::string speed_item, int map_number);

	void save_to_file();

	static SettingsKit load_from_file();
};