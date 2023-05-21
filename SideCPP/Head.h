#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "Helper.h"

#define DELIMITER ","
#define TYPE_DATE_SIZE 25
#define TYPE_INT_SIZE 5

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
	char* timeclockId = Helper::intToStrFile(&timeclock.id, TYPE_INT_SIZE);
	char* owner = Helper::intToStrFile(&timeclock.id, TYPE_INT_SIZE);
	char* startDate = Helper::timeToStrFile(&timeclock.startDate, TYPE_DATE_SIZE);
	char* endDate = Helper::timeToStrFile(&timeclock.endDate, TYPE_DATE_SIZE);
	sstr << *timeclockId << DELIMITER << *startDate << DELIMITER << *endDate << DELIMITER << *owner << endl;
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
