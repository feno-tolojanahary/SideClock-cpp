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
	currentAction = Action::CREATE;
	model.name = modelName;
	attrValues = {};
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
	switch (currentAction)
	{
		case Action::CREATE:
			execCreate();
		case Action::ADD_VAL:
			execAddVal();
		case Action::UPDATE_VAL:
			execUpdateVal();
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
	oss << model.name << CONF_DELIMITER;
	for (const Field& field : model.fields) {
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
	StorageBase storageBase(model.name);
	StorageBase* storage = &storageBase;
	vector<RowData> orderedValues{};
	
	for (const Value & attrVal : attrValues)
	{
		vector<string> lineValue(orderedColumns.size(), "");
		int indexStoreVal;
		for (const Field & currentField : orderedColumns) {
			if (attrVal.fieldName.compare(currentField.name) == 0) {

				lineValue.at(indexStoreVal) = attrVal.value;
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
	currentAction = Action::ADD_VAL;
	model.name = modelName;
	attrValues = {};
}

vector<vector<string>> Store::getVal(const string& modelName)
{
	currentAction = Action::GET_VAL;
	model.name = modelName;
	StorageBase *storage = new StorageBase(model.name);
	vector<vector<string>> data = storage->readData();
	return data;
}

void Store::andWhere(const string& fieldName, auto value)
{
	Type type = static_cast<string>(val);
	Field field(fieldName, type);
	condAttrValues.push_back(field);
}

void Store::updateVal(const string& modelName)
{
	currentAction = Action::UPDATE_VAL;
	model.name = modelName;
	attrValues = {};
	condAttrValues = {};
}

//void Store::execUpdateVal()
//{
//
//}