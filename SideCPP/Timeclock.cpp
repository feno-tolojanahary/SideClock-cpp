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
	string _startDate, _endDate;
	if (convertDate)
	{
		char buffStart[70], buffEnd[70];
		strftime(buffStart, sizeof buffStart, "%A %c", gmtime(&startDate));
		if (endDate > 0)
		{
			strftime(buffEnd, sizeof buffEnd, "%A %c", gmtime(&endDate));
		}
		_startDate.assign(buffStart);
		_endDate.assign(buffEnd);
	}
	else
	{
		_startDate = to_string(startDate);
		_endDate = to_string(endDate);
	}
	sstr << id << DELIMITER << _startDate << DELIMITER << _endDate << DELIMITER << to_string(owner) + "\n";
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