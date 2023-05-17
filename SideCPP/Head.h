#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Helper.h"

#define DATA_SEPARATOR ";"

using namespace std;

struct TimeClock 
{
	int id;
	int owner = 1;
	time_t startDate;
	time_t endDate;
};


string timeclockHeader() 
{
	string separator = (string)DATA_SEPARATOR;
	return "id" + separator + "startDate" + separator + "endDate" + separator + "owner";
}

string stringifyTimeclock(const TimeClock & timeclock) 
{
	stringstream sstr;
	sstr << timeclock.id << DATA_SEPARATOR << timeclock.startDate << DATA_SEPARATOR << timeclock.endDate << DATA_SEPARATOR << timeclock.owner << endl;
	return sstr.str();
}

TimeClock* parseTimeclock(const vector<string>& headers, const vector<string>& timeclockValues) 
{
	TimeClock* timeclock;
	int index = 0;
	for (const string& value : headers) {
		if (index < timeclockValues.size()) {
			if (value == "id") {
				timeclock->id = stoi(timeclockValues[index]);
			}
			else if (value == "startDate") {
				timeclock->startDate = Helper::stringToTime(timeclockValues[index]);
			}
			else if (value == "endDate") {
				timeclock->endDate = Helper::stringToTime(timeclockValues[index]);
			}
			else if (value == "owner") {
				timeclock->owner = stoi(timeclockValues[index]);
			}
		}
		index++;
	}
}