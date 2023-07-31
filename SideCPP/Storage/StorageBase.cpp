#include "StorageBase.h"
#include "../Helper.h"
#include <fstream>

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

bool StorageBase::saveData(vector<vector<string>> fileData)
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

	for (const vector<string> lineData : fileData)
	{
		for (const string& valueData : lineData)
		{
			file << valueData << DELIMITER;
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

	return content;
}

//UpdateResult updateData(vector<Condition> conditions, vector<vector<string>> update)
//{
//	
//}