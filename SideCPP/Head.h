#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "Helper.h"

#define DELIMITER ","

using namespace std;

struct TimeClock 
{
	int id;
	int owner = 1;
	time_t startDate = 0;
	time_t endDate = 0;
};

struct TimeClockOpt
{
	int owner = 1;
	time_t startDate = 0;
	time_t endDate = 0;
};

string timeclockHeader() 
{
	string separator = (string)DELIMITER;
	return "id" + separator + "startDate" + separator + "endDate" + separator + "owner";
}

string stringifyTimeclock(const TimeClock & timeclock) 
{
	stringstream sstr;
	sstr << timeclock.id << DELIMITER << timeclock.startDate << DELIMITER << timeclock.endDate << DELIMITER << timeclock.owner << endl;
	return sstr.str();
}

TimeClock parseTimeclock(const vector<string>& headers, const vector<string>& timeclockValues) 
{
	TimeClock timeclock;
	int index = 0;
	for (const string& value : headers) {
		if (index < timeclockValues.size()) {
			if (value == "id") {
				timeclock.id = stoi(timeclockValues[index]);
			}
			else if (value == "startDate") {
				timeclock.startDate = Helper::stringToTime(timeclockValues[index]);
			}
			else if (value == "endDate") {
				timeclock.endDate = Helper::stringToTime(timeclockValues[index]);
			}
			else if (value == "owner") {
				timeclock.owner = stoi(timeclockValues[index]);
			}
		}
		index++;
	}
	return timeclock;
}
