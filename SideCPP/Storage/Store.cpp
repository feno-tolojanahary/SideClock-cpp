#pragma once
#include "Store.h"
#include "StorageBase.h"
#include "../Helper.h"
#include <sstream>
#include <fstream>

Store::Store()
{
	// Get columns order indexed
	string line;
	fstream file(CONF_MODEL, fstream::out | fstream::app | fstream::binary);
	if (!file.is_open())
	{
		cout << "Error opening conf file..." << endl;
		return;
	}
	while (getline(file, line))
	{
		if (line.find(this->model.name) != string::npos)
		{
			vector<string> splitedLine = Helper::splitChar(line, CONF_DELIMITER);
			if (splitedLine[0].compare(this->model.name) == 0) {
				int lineIndex = 0;
				for (const string& field : splitedLine) {
					lineIndex++;
					if (lineIndex > 1) {
						vector<string> fieldInfo = Helper::splitChar(field, CONF_FIELD_DELIMITER);
						orderedColumns.push_back(make_pair(lineIndex - 1, fieldInfo[0]));
					}
				}
			}
		}
	}
	file.close();
}

void Store::createModel(const string& modelName)
{
	this->currentAction = Action::CREATE;
	this->model.name = modelName;
	this->attrValues = {};
}

void Store::field(const string& fieldName, auto val)
{
	if (this->currentAction == Action::CREATE) {
		Type type = static_cast<string>(val);
		Field field(fieldName, type);
		this->model.fields.push_back(field);
	}
	else if (this->currentAction == Action::ADD_VAL || this->currentAction == Action::UPDATE_VAL) {
		pair<string, string> assignedAttrVal(fieldName, value);
		this->attrValues.push_back(assignedAttrVal);
	}
}

void Store::exec()
{
	switch (this->currentAction)
	{
		case Action::CREATE:
			this->execCreate();
		case Action::ADD_VAL:
			this->execAddVal();
		case Action::UPDATE_VAL:
			this->execUpdateVal();
		default:
			break;
	}
}

void Store::execCreate()
{
	ostringstream oss;
	fstream file(CONF_MODEL, fstream::out | fstream::app | fstream::binary);
	if (!file.is_open())
	{
		cout << "Error opening conf file..." << endl;
		return;
	}
	oss << this->model.name << CONF_DELIMITER;
	for (const Field& field : this->model.fields) {
		oss << field.name << CONF_FIELD_DELIMITER << static_cast<char>(field.type) << CONF_FIELD_DELIMITER << field.length;
		oss << CONF_DELIMITER;
	}
	oss << "\n";
	file << oss.str();
	file.close();
}

void Store::execAddVal()
{
	// Call value storage on database
	StorageBase storageBase(this->model.name);
	StorageBase* storage = &storageBase;
	vector<vector<string>> orderedValues{};
	
	for (const pair<string, string> attrVal : this->attrValues)
	{
		vector<string> lineValue(orderedColumns.size(), "");
		int indexStoreVal;
		for (const pair<int, string> orderFieldInfo : orderedColumns) {
			if (attrVal.first.compare(orderFieldInfo.second) == 0) {
				lineValue.at(indexStoreVal) = attrVal.second;
				orderedValues.push_back(lineValue);
			}
		}
	}

	if (storage->saveData(orderedValues)) {
		cout << "saved with success." << endl;
	}
	else {
		cout << "Error saving data" << endl;
	}
}

void Store::addVal(const string& modelName)
{
	this->currentAction = Action::ADD_VAL;
	this->model.name = modelName;
	this->attrValues = {};
}

vector<vector<string>> Store::getVal(const string& modelName)
{
	this->currentAction = Action::GET_VAL;
	this->model.name = modelName;
	StorageBase *storage = new StorageBase(this->model.name);
	vector<vector<string>> data = storage->readData();
	return data;
}

void Store::andWhere(const string& fieldName, auto value)
{
	Type type = static_cast<string>(val);
	Field field(fieldName, type);
	this->condAttrValues.push_back(field);
}

void Store::updateVal(const string& modelName)
{
	this->currentAction = Action::UPDATE_VAL;
	this->model.name = modelName;
	this->attrValues = {};
	this->condAttrValues = {};
}

//void Store::execUpdateVal()
//{
//
//}