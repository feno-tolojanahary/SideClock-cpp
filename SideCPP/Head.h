#include <iostream>
#include <sstream>
#define DATA_SEPARATOR ";"

struct TimeClock {
	std::time_t startDate;
	std::time_t endDate;
};

std::string stringifyTimeclock(const TimeClock & timeclock) {
	std::stringstream sstr;
	sstr << timeclock.startDate << DATA_SEPARATOR << timeclock.endDate << endl;
	return sstr.str();
}