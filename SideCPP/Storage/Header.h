#pragma once
#include <iostream>
#include <vector>

enum class Type : char {
	TYPE_INT = 'n',
	TYPE_CHAR = 's',
	TYPE_DATE = 'd',
	TYPE_ANY
};

struct RowData {
	vector<Value> data;
};

struct Condition {
	string attr;
	string value;
};

enum class Action {
	CREATE,
	ADD_VAL,
	UPDATE_VAL,
	DELETE_VAL,
	GET_VAL
};

struct Field {
	short range = -1;
	std::string name;
	Type type;
	int length = 200;
	 
	bool operator==(const Field& rfield)
	{
		return name == rfield.name;
	}
};

struct Value {
	std::string fieldName;
	std::string value;

	bool operator==(const Value& rValue)
	{
		return fieldName == rValue.fieldName;
	}
};

struct ModelCreate {
	std::string name;
	std::vector<Field> fields;
};

struct Model {
	std::vector<std::string> values;
};

const std::string CONF_MODEL = "conf_model";
const char CONF_DELIMITER = ';';
const char CONF_FIELD_DELIMITER = '|';


Type getType(const char& typeIndex) {
	switch (typeIndex) {
	case 'n':
		return Type::TYPE_INT;
	case 's':
		return Type::TYPE_CHAR;
	case 'd':
		return Type::TYPE_DATE;
	default:
		return Type::TYPE_ANY;
	}
}