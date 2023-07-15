#pragma once
#include "Store.h"
#include <sstream>

Store* Store::createModel(const string& modelName)
{
	this->model.name = modelName;
	return this;
}

Store* Store::field(const string& fieldName, Type type)
{
	Field field(fieldName, type);
	this->model.fields.push_back(field);
	return this;
}