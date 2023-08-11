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

struct RowData {
	vector<Value> data;
};

class StorageBase {

public:
	StorageBase(const string& fileName);

	bool saveData(vector<RowData> listRawData);
	vector<vector<string>> readData();
	string parseQuery(std::shared_ptr<RowData> rowData);
	UpdateResult* updateData(vector<Condition> conditions, vector<Value> update);

private:
	string filename;
	vector<Field> currentColumnsInfo;
};