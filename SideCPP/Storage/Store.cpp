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
		if (line.find(model.name) != string::npos)
		{
			vector<string> modelChains = Helper::splitChar(line, CONF_DELIMITER);
			if (modelChains[0].compare(model.name) == 0) {
				int lineIndex = 0;
				for (const string& fieldInfo : modelChains) {
					lineIndex++;
					if (lineIndex > 1) {
						vector<string> fieldChains = Helper::splitChar(fieldInfo, CONF_FIELD_DELIMITER);
						Field definedField;
						definedField.range = lineIndex;
						definedField.name = fieldChains[0];
						definedField.type = getType(*(fieldChains[1].data()));
						definedField.length = stoi(fieldChains[2]);
						orderedColumns.push_back(definedField);
					}
				}
			}
		}
	}
	file.close();
}

void Store::createModel(const string& modelName)
{
	action = Action::CREATE;
	model.name = modelName;
	pinnedValues = {};
}

void Store::field(const string& fieldName, auto val)
{
	if (action == Action::CREATE) {
		Type type = static_cast<string>(val);
		Field field(fieldName, type);
		model.fields.push_back(field);
	}
	else if (action == Action::ADD_VAL || action == Action::UPDATE_VAL) {
		Value value{
			.fieldName = fieldName,
			.value = val
		}
		pinnedValues.push_back(value);
	}
}

void Store::exec()
{
	switch (action)
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
	std::unique_ptr<StorageBase> storage = make_unique<StorageBase>(model.name);
	vector<RowData> savingRowData{};

	RowData oneRowData;	
	for (const Value & pinnedVal : pinnedValues)
	{
		int indexStoreVal;
		for (const Field & field : orderedColumns) {
			if (pinnedVal.fieldName.compare(field.name) == 0) {
				oneRowData.data.push_back(pinnedVal);
			}

		}

		savingRowData.toSaveValue(lineValue);
	}

	if (storage->saveData(savingRowData)) {
		cout << "saved with success." << endl;
	}
	else {
		cout << "Error saving data" << endl;
	}
}

void Store::addVal(const string& modelName)
{
	action = Action::ADD_VAL;
	model.name = modelName;
	pinnedValues = {};
}

vector<vector<string>> Store::getVal(const string& modelName)
{
	action = Action::GET_VAL;
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
	action = Action::UPDATE_VAL;
	model.name = modelName;
	pinnedValues = {};
	condAttrValues = {};
}

//void Store::execUpdateVal()
//{
//
//}