#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

#define DELIMITER ','

using namespace std;
class Helper {

public: 

	static vector<string> splitChar(string lineStr, char delimiter)
	{
		vector<string> spliteStr;
		size_t pos = 0;
		while ((pos = lineStr.find(delimiter)) != std::string::npos) {
			string token = lineStr.substr(0, pos);
			spliteStr.push_back(token);
			lineStr.erase(0, pos + 1);
		}
		return spliteStr;
	}

	static time_t stringToTime(string timeStr) 
	{
		struct tm tm;
		istringstream isstr(timeStr);
		isstr >> get_time(&tm, "%a %b %d %H:%M:%S %Y");
		time_t t = mktime(&tm);
		return t;
	}

	/*static void fillCharEmptySpace(char characters[], const int& valSize, const int& size)
	{
		for (int i = valSize + 1; i < size; i++)
		{
			characters[i] = ' ';
		}
		characters[size] = '\0';
	}

	static char* timeToStrFile(const time_t *t, const int &size) 
	{
		char* timeChar = new char[size];

		if (t == 0)
		{	
			fillCharEmptySpace(timeChar, 0, size);
			return timeChar;
		}
		else 
		{
			return ctime(t);
		}
			
	}

	static char* intToStrFile(const int* value, const int &size)
	{
		string strFile = std::to_string((int) & value);
		char* arrChar = new char[size];
		strcpy(arrChar, strFile.c_str());
		fillCharEmptySpace(arrChar, strlen(arrChar), size);
		return arrChar;
	}*/
};