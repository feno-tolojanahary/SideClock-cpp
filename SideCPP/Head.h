#include <iostream>
#define DATA_SEPARATOR ";"

struct TimeClock {
	std::time_t startDate;
	std::time_t endDate;
};

std::string stringifyTimeclock(const TimeClock & timeclock) {

	return timeclock.startDate.str();
}