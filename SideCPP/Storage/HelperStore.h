#pragma once
#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

Field fieldByName(const string& fieldName, vector<Field> columnsInfo) 
{
	for (vector<Field>::iterator it = columnsInfo.begin(); it != columnsInfo.end(); it++)
	{
		if (it->name == fieldName) {
			return *it;
		}
	}
}

// duplicate
vector<string> splitChar(string lineStr, char delimiter)
{
	vector<string> spliteStr;
	size_t pos = 0;
	while ((pos = lineStr.find(delimiter)) != std::string::npos) {
		string token = lineStr.substr(0, pos);
		spliteStr.push_back(token);
		lineStr.erase(0, pos + 1);
	}
	spliteStr.push_back(lineStr);
	return spliteStr;
}

// duplicate
string trim(const string& str, const string& whitespace = " \t")
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}