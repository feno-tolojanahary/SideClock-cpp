#pragma once
#include "Store.h"
#include "StorageBase.h"
#include "../Helper.h"
#include <sstream>
#include <fstream>

void Store::createModel(const string& modelName)
{
	this->currentAction = Action::CREATE;
	this->model.name = modelName;
	this->attrValues = {};
}

void Store::field(const string& fieldName, auto val)
{
	if (this->currentAction == Action::CREATE) {
		Type type = static_cast<char>(val);
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
	vector<string> fields;

	fstream file(CONF_MODEL, fstream::in | fstream::app | fstream::binary);
	if (!file.is_open()) {
		cout << "Error opening conf file..." << endl;
		return;
	}
	
	string modelInfo;
	string line;
	vector<pair<int, string>> orderedFieldNames{};
	int headFieldIndex = 0;
	
	while (getline(file, line))
	{
		if (line.find(this->model.name) != string::npos) {
			vector<string> splitedModelInfo = Helper::splitChar(line, CONF_DELIMITER);
			if (splitedModelInfo.size() == 0)
				continue;
			if (splitedModelInfo[0].compare(this->model.name) != 0)
				continue;
			for (const string& modelInfo : splitedModelInfo)
			{
				if (modelInfo.compare(this->model.name) == 0)
					continue;
				if (modelInfo.find(CONF_FIELD_DELIMITER) != string::npos) {
					vector<string> fieldInfo = Helper::splitChar(line, CONF_FIELD_DELIMITER);
					orderedFieldNames.push_back(make_pair(headFieldIndex, fieldInfo[0]));
					headFieldIndex++;
				}
			}
		}
	}

	vector<vector<string>> orderedValues{};
	
	for (const pair<string, string> attrVal : this->attrValues)
	{
		vector<string> lineValue(orderedFieldNames.size(), "");
		int indexStoreVal;
		for (const pair<int, string> orderFieldInfo : orderedFieldNames) {
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

void Store::updateVal(const string& modelName)
{
	this->currentAction = Action::UPDATE_VAL;
	this->model.name = modelName;
	this->attrValues = {};
}
