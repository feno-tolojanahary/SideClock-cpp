#include "StoreHandler.h"
#include "../Helper.h"
#include <fstream>

bool StoreHandler::saveData(vector<vector<string>> fileData)
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