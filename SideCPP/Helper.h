#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

#define DELIMITER '|'
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
		spliteStr.push_back(lineStr);
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
		tmDate.tm_mday = date;
		tmDate.tm_year = year;

		tmDate.tm_hour = 0;
		tmDate.tm_min = 0;
		tmDate.tm_sec = 0;
		return mktime(&tmDate);
	}

	static short lastDayOfMonth(const short& month, const int& year) 
	{
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

	static vector<time_t> allDatesOfMonth(const short& month, const int& year) 
	{
		vector<time_t> dateList;
		short lastDay = Helper::lastDayOfMonth(month, year);

		for (short i = 1; i <= lastDay; i++)
		{
			time_t dateOfMonth = Helper::createDate(i, month, year);
			dateList.push_back(dateOfMonth);
		}

		return dateList;
	}

	template <typename T>
	static void emplaceMatchDateOnMonth(vector<string>* lineContent, const time_t& dateOfMonth, const T& elem)
	{
		struct tm* tmElemDate, _tmElemDate;
		struct tm* tmDateOfMonth, _tmDateOfMonth;
		tmElemDate = &_tmElemDate;
		tmDateOfMonth = &_tmDateOfMonth;

		gmtime_s(tmElemDate, &dateOfMonth);
		time_t startDate = elem.getStartDate();
		gmtime_s(tmDateOfMonth, &startDate);

		if (tmElemDate->tm_year == tmDateOfMonth->tm_year
			&& tmElemDate->tm_mon == tmDateOfMonth->tm_mon
			&& tmElemDate->tm_mday == tmDateOfMonth->tm_mday)
		{
			lineContent->push_back(elem.getStrDate());
		}
		else {
			lineContent->push_back("");
		}
	}

	static string hourMinutesStrDiff(time_t endDate, time_t startDate)
	{
		int hours, minutes;
		double diffSeconds = difftime(endDate, startDate);
		hours = static_cast<int>(floor(diffSeconds / 3600));
		minutes = static_cast<int>((diffSeconds / 60) - (hours * 60));
		stringstream sstr;
		sstr << setfill('0') << setw(2) << hours << ":" << setfill('0') << setw(2) << minutes;
		return sstr.str();
	}

	static short getWeekNumber(const short& month, const int& year)
	{
		struct tm tmStartMonthDate, tmEndMonthDate;
		memset(&tmStartMonthDate, 0, sizeof(tmStartMonthDate));
		memset(&tmEndMonthDate, 0, sizeof(tmEndMonthDate));
		short lastDayOfMonth = Helper::lastDayOfMonth(month, year);
	
		tmStartMonthDate.tm_year = year - 1900;
		tmStartMonthDate.tm_mon = month - 1;
		tmStartMonthDate.tm_mday = 1;
		
		tmEndMonthDate.tm_year = year - 1900;
		tmEndMonthDate.tm_mon = month - 1;
		tmEndMonthDate.tm_mday = lastDayOfMonth;
		mktime(&tmStartMonthDate);
		mktime(&tmEndMonthDate);
		char buffStartWeekOfYear[3], buffEndWeekOfYear[3];
		strftime(buffStartWeekOfYear, sizeof buffStartWeekOfYear, "%W", &tmStartMonthDate);
		strftime(buffEndWeekOfYear, sizeof buffEndWeekOfYear, "%W", &tmEndMonthDate);

		return stoi(buffEndWeekOfYear) - stoi(buffEndWeekOfYear) + 1;
	}

	static string trim(const string& str, const string& whitespace = " \t")
	{
		const auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == string::npos)
			return ""; // no content

		const auto strEnd = str.find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}
};