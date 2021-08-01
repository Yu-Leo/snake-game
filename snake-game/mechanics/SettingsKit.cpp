#include "SettingsKit.h"

#include <fstream>

SettingsKit::SettingsKit() {
	this->volume = 0;
	this->speed_item = "";
	this->map_number = 0;
}

SettingsKit::SettingsKit(int volume, std::string speed_item, int map_number) {
	this->volume = volume;
	this->speed_item = speed_item;
	this->map_number = map_number;
}

void SettingsKit::save_to_file() {
	std::ofstream fout;
	fout.open(FILE_NAME);
	if (!fout.is_open()) {
		throw std::exception("Settings file opening error");
	}
	fout.write((char*)&(*this), sizeof(SettingsKit));
	fout.close();
}

SettingsKit SettingsKit::load_from_file() {
	std::ifstream fin;
	fin.open(FILE_NAME);
	if (!fin.is_open()) {
		throw std::exception("Settings file opening error");
	}
	SettingsKit result;
	fin.read((char*)&result, sizeof(SettingsKit));
	fin.close();
	return result;
}