#include <iostream>
#include <sstream>
#define DATA_SEPARATOR ";"

struct TimeClock {
	int id;
	int owner = 1;
	std::time_t startDate;
	std::time_t endDate;
};


std::string timeclockHeader() {
	std:string separator = (std::string)DATA_SEPARATOR;
	return "id" + separator + "startDate" + separator + "endDate" + separator + "owner";
}

std::string stringifyTimeclock(const TimeClock & timeclock) {
	std::stringstream sstr;
	sstr << timeclock.id << DATA_SEPARATOR << timeclock.startDate << DATA_SEPARATOR << timeclock.endDate << DATA_SEPARATOR << timeclock.owner << endl;
	return sstr.str();
}