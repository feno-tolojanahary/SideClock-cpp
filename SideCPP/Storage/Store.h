#pragma once
#include "Header.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Store {

public:
	Store();
	void createModel(const string& modelName);
	void field(const string& fieldName, auto val);
	void exec();
	void addVal(const string& modelName);
	vector<vector<string>> getVal(const string& modelName);
	//void getVal(const string& modelName, vector<string> selectedFields);
	void updateVal(const string& modelName);
	void andWhere(const string& fieldName, auto value);

private:
	void execCreate();
	void execAddVal();
	void execUpdateVal();
	void execGetVal();

	Action currentAction = Action::CREATE;
	ModelCreate model;
	vector<pair<int, string>> orderedColumns;
	vector<Value> attrValues;
	vector<Value> condAttrValues;
};