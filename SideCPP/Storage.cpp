#include <fstream>
#include <string>
#include "Storage.h"

void Storage::saveData(const string & data) {
	file.open(filename, ios::out | ios::app | ios::binary);
	if (file.is_open()) {
		file << data << std::endl;
		file.close();
	}
}

vector<string> Storage::readData() {
	vector<string> content;
	string line;
	file.open(filename, ios::out | ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			content.push_back(line);
		}
	}

	return content;
}