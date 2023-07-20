#include "StorageBase.h"
#include "../Helper.h"
#include <fstream>

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