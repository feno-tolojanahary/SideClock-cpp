#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

enum class Type {
	TYPE_INT = 1,
	TYPE_CHAR = 2,
	TYPE_DATE = 3
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


const string CONF_MODEL = "conf_model";
const string CONF_DELIMITER = ";";
const string CONF_FIELD_DELIMITER = "|";

class Store {

public:
	void createModel(const string& modelName);
	void field(const string& fieldName, Type type);
	Model addVal(const string& modelName);
	Model field(const string& fieldName, auto& val);
	void exec();

private:
	ModelCreate model;
};