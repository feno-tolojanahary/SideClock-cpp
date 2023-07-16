#pragma once
#include "Store.h"
#include <sstream>

void Store::createModel(const string& modelName)
{
	this->model.name = modelName;
}

void Store::field(const string& fieldName, Type type)
{
	Field field(fieldName, type);
	this->model.fields.push_back(field);
}
