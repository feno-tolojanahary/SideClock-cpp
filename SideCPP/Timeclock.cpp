#include <string>
#include <ctime>
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

string TimeClock::stringify(bool convertDate = false) const
{
	stringstream sstr;
	string _startDate = convertDate ? ctime(&startDate) : to_string(static_cast<long int>(startDate));
	string _endDate = convertDate ? ctime(&endDate) : to_string(static_cast<long int>(endDate));
	sstr << id << DELIMITER << _startDate << DELIMITER << _endDate << DELIMITER << std::to_string(owner) + "\n";
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