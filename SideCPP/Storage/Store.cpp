#pragma once
#include "Store.h"
#include <sstream>
#include <fstream>

void Store::createModel(const string& modelName)
{
	this->model.name = modelName;
}

void Store::field(const string& fieldName, Type type)
{
	Field field(fieldName, type);
	this->model.fields.push_back(field);
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
		oss << field.name << CONF_FIELD_DELIMITER << field.type << CONF_FIELD_DELIMITER << field.length;
		oss << CONF_DELIMITER;
	}
	oss << "\n";
	file << oss.str();
}