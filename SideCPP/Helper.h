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

	static time_t stringToTime(const string &timeStr, const char* format = "%a %b %d %H:%M:%S %Y") 
	{
		struct tm tm;
		istringstream isstr(timeStr);
		isstr >> get_time(&tm, format);
		time_t t = mktime(&tm);
		return t;
	}

	static time_t createDate(const short& date, const short& month, const int& year)
	{
		struct tm tmDate;
		tmDate.tm_mon = month;
		tmDate.tm_wday = date;
		tmDate.tm_year = year;

		tmDate.tm_hour = 0;
		tmDate.tm_min = 0;
		tmDate.tm_sec = 0;
		return mktime(&tmDate);
	}

	static short lastDayOfMonth(short month, int year) {
		if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
			return 31;
		else if (month == 3 || month == 5 || month == 8 || month == 10)
			return 30;
		else {
			if (year % 4 == 0) {
				if (year % 100 == 0) {
					if (year % 400 == 0)
						return 29;
					return 28;
				}
				return 29;
			}
			return 28;
		}
	}

	static vector<time_t> allDatesOfMonth(short month, int year) {
		vector<time_t> dateList;
		short lastDay = Helper::lastDayOfMonth(month, year);

		for (short i = 1; i <= lastDay; i++)
		{
			time_t dateOfMonth = Helper::createDate(i, month, year);
			dateList.push_back(dateOfMonth);
		}

		return dateList;
	}
};