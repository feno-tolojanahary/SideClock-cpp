#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class StoreHandler {

public:
	StoreHandler(string fileName): filename(fileName) {}

	bool saveData(vector<vector<string>> data);

private:
	string filename;
};