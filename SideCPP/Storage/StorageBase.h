#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include "Header.h"

using namespace std;

class StorageBase {

public:
	StorageBase(const string& fileName);

	bool saveData(vector<RowData> listRawData);
	vector<vector<string>> readData();
	string parseQuery(std::shared_ptr<RowData> rowData);
	UpdateResult* updateData(vector<Condition> conditions, vector<Value> update);
	void deleteData(vector<Condition> conditions);
	vector<string> findOne(vector<Condition> conditions);

private:
	string filename;
	vector<Field> currentColumnsInfo;
};