#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Condition {
	pair<string, string> attrVal;
};

class StorageBase {

public:
	StorageBase(string fileName): filename(fileName) {}

	bool saveData(vector<vector<string>> data);
	vector<vector<string>> readData();
	//vector<string> updateData(vector<Condition> conditions, vector<vector<string>> update);

private:
	string filename;
};