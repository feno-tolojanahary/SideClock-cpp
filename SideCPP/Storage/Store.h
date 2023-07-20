#pragma once
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

enum class Type: char {
	TYPE_INT = 'n',
	TYPE_CHAR = 's',
	TYPE_DATE = 'd'
};

enum class Action {
	CREATE,
	ADD_VAL,
	UPDATE_VAL,
	DELETE_VAL
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
const char CONF_DELIMITER = ';';
const char CONF_FIELD_DELIMITER = '|';

class Store {

public:
	void createModel(const string& modelName);
	void field(const string& fieldName, auto val);
	void addVal(const string& fieldName, auto value);
	void exec();

private:
	void execCreate();
	void execAddVal();

	Action currentAction = Action::CREATE;
	ModelCreate model;
	vector<pair<string, string>> attrValues;
};