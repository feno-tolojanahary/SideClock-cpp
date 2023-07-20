#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class StorageBase {

public:
	StorageBase(string fileName): filename(fileName) {}

	bool saveData(vector<vector<string>> data);
	vector<vector<string>> readData();

private:
	string filename;
};