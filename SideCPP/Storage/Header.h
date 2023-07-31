#pragma once
#include <iostream>
#include <vector>

enum class Type : char {
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
	std::string name;
	Type type;
	int length = 200;
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