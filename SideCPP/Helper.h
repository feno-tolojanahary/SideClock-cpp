#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

#define DELIMITER ','
#define DELIMITER_DATE '/'
#define DELIMITER_HOUR ':'

#define FORMAT_DATE "%m/%d/%Y"
#define FORMAT_HOUR "%H:%S"
#define FORMAT_DATE_HOUR "%m/%d/%Y %H:%S"

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

	static time_t stringToTime(string timeStr, const char* format = "%a %b %d %H:%M:%S %Y") 
	{
		struct tm tm;
		istringstream isstr(timeStr);
		isstr >> get_time(&tm, format);
		time_t t = mktime(&tm);
		return t;
	}
};