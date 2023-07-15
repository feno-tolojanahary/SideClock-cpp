#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

enum Type {
	INT,
	CHAR,
	DATE
};

struct Field {
	string name;
	Type type;
	int length = 200;
};

struct ModelCreate {
	string name;
	vector<Field> fields;
};

struct Model {
	vector<string> values;
};

class Store {
public:
	Store* createModel(const string& modelName);
	Store* field(const string& fieldName, Type type);
	Model addVal(const string& modelName);
	Model field(const string& fieldName, auto& val);
	void exec();

private:
	ModelCreate model;
};