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
	DELETE_VAL,
	GET_VAL
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
	vector<pair<string, string>> attrValues;
	vector<pair<string, string>> condAttrValues;
};