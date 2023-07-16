#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

enum class Type {
	TYPE_INT,
	TYPE_CHAR,
	TYPE_DATE
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
	const string CONF_MODEL = "conf_model";

public:
	void createModel(const string& modelName);
	void field(const string& fieldName, Type type);
	Model addVal(const string& modelName);
	Model field(const string& fieldName, auto& val);
	void exec();

private:
	ModelCreate model;
};