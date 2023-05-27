#include <string>
#include "TimeClock.h"
#include "Helper.h"


TimeClock::~TimeClock()
{

}

string TimeClock::getStrHeader() const
{
	stringstream sstr;
	sstr << "id" << DELIMITER << "startDate" << DELIMITER << "endDate" << DELIMITER << "owner\n";
	return sstr.str();
}

string TimeClock::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << startDate << DELIMITER << endDate << DELIMITER << std::to_string(owner) + "\n";
	return sstr.str();
}

void TimeClock::populateStr(const vector<string>& headers, const vector<string>& timeclockValues)
{
	int index = 0;
	for (const string& value : headers) {
		if (index < timeclockValues.size()) {
			if (value == "id") {
				this->setId(stoi(timeclockValues[index]));
			}
			else if (value == "startDate") {
				this->setStartDate(stoi(timeclockValues[index]));
			}
			else if (value == "endDate") {
				this->setEndDate(stoi(timeclockValues[index]));
			}
			else if (value == "owner") {
				this->setOwner(stoi(timeclockValues[index]));
			}
		}
		index++;
	}
}