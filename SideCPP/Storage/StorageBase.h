#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include "Header.h"

using namespace std;

struct Condition {
	string attr;
	string value;
};

struct UpdateResult {
	int udpatedCount = 0;
	bool isSuccess = false;
};

class StorageBase {

public:
	StorageBase(const string& fileName);

	bool saveData(vector<vector<string>> data);
	vector<vector<string>> readData();
	//UpdateResult updateData(vector<Condition> conditions, vector<vector<string>> update);

private:
	string filename;
	vector<Field> currentColumnsInfo;
};