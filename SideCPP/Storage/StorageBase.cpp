#include "StorageBase.h"
#include "../Helper.h"
#include "HelperStore.h"
#include <fstream>
#include <iomanip>

StorageBase::StorageBase(const string& fileName)
{
	this->filename = fileName;

	string line;
	fstream file(CONF_MODEL, fstream::out | fstream::app | fstream::binary);
	if (!file.is_open())
	{
		cout << "Error opening conf file..." << endl;
		return;
	}
	while (getline(file, line))
	{
		if (line.find(fileName) != string::npos)
		{
			vector<string> splitedLine = Helper::splitChar(line, CONF_DELIMITER);
			if (splitedLine[0].compare(fileName) == 0) {
				int lineIndex = 0;
				for (const string& field : splitedLine) {
					lineIndex++;
					if (lineIndex > 1) {
						vector<string> fieldInfo = Helper::splitChar(field, CONF_FIELD_DELIMITER);
						Field field;
						field.name = fieldInfo[0];
						if (*(fieldInfo[1].data()) == 'n') {
							field.type = Type::TYPE_INT;
						}
						else if (*(fieldInfo[1].data()) == 's') {
							field.type = Type::TYPE_CHAR;
						}
						else if (*(fieldInfo[1].data()) == 'n') {
							field.type == Type::TYPE_DATE;
						}
						field.length = stoi(fieldInfo[2]);
						currentColumnsInfo.push_back(field);
					}
				}
			}
		}
	}
	file.close();
}

bool StorageBase::saveData(vector<RowData> listRowData)
{
	streampos begin, end;
	string line;
	fstream file(filename, fstream::out | fstream::app | fstream::binary);
	if (!file.is_open())
	{
		return false;
	}

	file.seekg(0, ios::end);
	end = file.tellg();

	for (const RowData lineData : listRowData)
	{
		for (const Value valData : lineData.data) {
			const Field fieldInfo = fieldByName(valData.fieldName, currentColumnsInfo);
			file << setw(fieldInfo.length) << valData.value << setfill(' ') << DELIMITER;
		}
		file << "\n";
	}

	file.close();
	return true;
}

vector<vector<string>> StorageBase::readData()
{
	vector<vector<string>> content;
	string line;
	fstream file(filename, fstream::in | fstream::binary);
	if (!file.is_open())
	{
		return content;
	}
	while (getline(file, line)) {
		if (line.size() > 0) {
			vector<string> valLines = Helper::splitChar(line, DELIMITER);
			content.push_back(valLines);
		}
	}
	file.close();
	return content;
}

UpdateResult* StorageBase::updateData(vector<Condition> conditions, vector<Value> update)
{
	string line;
	std::unique_ptr<UpdateResult> res = std::make_unique<UpdateResult>();
	vector<pair<long long int, RowData>> foundRowData;
	fstream file(filename, fstream::in | fstream::out | fstream::binary);
	res->isSuccess = false;
	res->udpatedCount = 0;

	if (!file.is_open())
	{
		file.close();
		cout << "Error opening file for update" << endl;
		return res.get();
	}
	long long int pos = 0;
	
	for (line; getline(file, line);)
	{
		// first check by string
		bool isDetected = false;
		for (const Condition cond : conditions) {
			if (line.find(cond.value) != string::npos) {
				isDetected = true;
			}
			else {
				isDetected = false;
				break;
			}
		}
		if (!isDetected) {
			break;
		}
		// second check real equal
		vector<string> rowDataStr = splitChar(line, DELIMITER);
		RowData curRowData;
		vector<Value> currentFieldValues;
		int index = 0;
		for (const Field& field : currentColumnsInfo)
		{
			Value value;
			value.fieldName = field.name;
			value.value = trim(rowDataStr[index]);
			currentFieldValues.push_back(value);
			index++;
		}
		
		curRowData.data = currentFieldValues;

		for (const Condition& cond : conditions)
		{
			for (const Value& dataVal : curRowData.data)
			{
				if (cond.fieldName == dataVal.fieldName) {
					if (cond.value != dataVal.value) {
						isDetected = false;
					}
				}
			}
		}

		if (!isDetected) {
			break;
		}
		

		pos = file.tellg();
	
		foundRowData.push_back(make_pair(pos, curRowData));
	}


	if (pos == 0 && foundRowData.size() == 0) {
		file.close();
		return res.get();
	}

	// Update line on file
	for (const pair<long long int, RowData> rowDataPos : foundRowData)
	{
		std::shared_ptr<RowData> newRowData = std::make_shared<RowData>();
		for (Value val : rowDataPos.second.data)
		{
			for (const Value& valUpdate : update)
			{
				if (val.fieldName == valUpdate.fieldName)
				{
					val.value = valUpdate.value;
				} 
			}
			newRowData->data.push_back(val);
		}

		// directly write update on file
		const string rowParsed = parseQuery(newRowData);
		file.seekg(rowDataPos.first);
		file << rowParsed;
	}

	file.close();

	return res.get();
}

string StorageBase::parseQuery(std::shared_ptr<RowData> rowData)
{
	ostringstream osstr;
	for (const Value valData : rowData->data) {
		const Field fieldInfo = fieldByName(valData.fieldName, currentColumnsInfo);
		osstr << setw(fieldInfo.length) << valData.value << setfill(' ') << DELIMITER;
	}
	osstr << "\n";
	return osstr.str();
}

void StorageBase::deleteData(vector<Condition> conditions) 
{
	
}