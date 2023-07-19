#pragma once
#include "Store.h"
#include <sstream>
#include <fstream>

void Store::createModel(const string& modelName)
{
	this->currentAction = Action::CREATE;
	this->model.name = modelName;
}

void Store::field(const string& fieldName, auto val)
{
	if (this->currentAction == Action::CREATE) {
		Type type = static_cast<char>(val);
		Field field(fieldName, type);
		this->model.fields.push_back(field);
	}
	else if (this->currentAction == Action::ADD_VAL) {
		pair<string, string> assignedAttrVal(fieldName, value);
		this->attrValues.push_back(assignedAttrVal);
	}
}

void Store::exec()
{
	ostringstream oss;
	fstream file(CONF_MODEL, fstream::out | fstream::app | fstream::binary);
	if (!file.is_open())
	{
		return;
	}
	oss << this->model.name << CONF_DELIMITER;
	for (const Field& field : this->model.fields) {
		oss << field.name << CONF_FIELD_DELIMITER << static_cast<char>(field.type) << CONF_FIELD_DELIMITER << field.length;
		oss << CONF_DELIMITER;
	}
	oss << "\n";
	file << oss.str();
}

void Store::addVal(const string& fieldName, auto value)
{
	this->currentAction = Action::ADD_VAL;
	this->model.name = modelName;
}
