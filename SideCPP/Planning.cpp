#include <string>
#include <vector>
#include "Planning.h"
#include "Helper.h"

Planning::Planning(string strStartDate, string strEndDate, string strStartHour, string strEndHour)
{
	if (strStartDate.size() == 10) {
		startDate = Helper::stringToTime(strStartDate, FORMAT_DATE);
	}
	if (strStartHour.size() == 5) {
		startHour = Helper::stringToTime(strStartHour, FORMAT_HOUR);
	}
	if (strEndHour.size() == 5) {
		endHour = Helper::stringToTime(strEndHour, FORMAT_HOUR);
	}
	if (strEndDate.size() == 5)
	{
		endDate = Helper::stringToTime(strEndDate, FORMAT_DATE);
	}
}

string Planning::getStrHeader() const
{
	stringstream sstr;
	sstr << "id" << DELIMITER << "startDate" << DELIMITER << "endDate" << DELIMITER << "startHour" << DELIMITER << "endHour\n";
	return sstr.str();
}

string Planning::getStrDate() const
{
	char buffDate[10];
	time_t diffTime;
	if (endDate == 0)
	{
		return "in progress...";
	}
	diffTime = difftime(endDate, startDate);
	strftime(buffDate, sizeof buffDate, FORMAT_HOUR, gmtime(&diffTime));
	return buffDate;
}

string Planning::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << startDate << DELIMITER << endDate << DELIMITER << startHour << DELIMITER << endHour + "\n";
	return sstr.str();
}

string Planning::strOutput() const
{
	stringstream sstr;
	char buffStartDate[10], buffEndDate[10], buffStartHour[5], buffEndHour[5];

	strftime(buffStartDate, sizeof buffStartDate, FORMAT_DATE, gmtime(&startDate));
	strftime(buffEndDate, sizeof buffEndDate, FORMAT_DATE, gmtime(&endDate));
	strftime(buffStartHour, sizeof buffStartHour, FORMAT_HOUR, gmtime(&startHour));
	strftime(buffEndHour, sizeof buffEndHour, FORMAT_HOUR, gmtime(&endHour));

	sstr << id << DELIMITER << buffStartDate << DELIMITER << buffEndDate << DELIMITER << buffStartHour << DELIMITER << buffEndHour << "\n";
	return sstr.str();
}

void Planning::populateStr(const vector<string>& headers, const vector<string>& panningValues)
{
	int index = 0;
	for (const string& value : headers) {
		if (index < panningValues.size()) {
			if (value == "id") {
				this->setId(stoi(panningValues[index]));
			}
			else if (value == "startDate") {
				this->setStartDate(stoi(panningValues[index]));
			}
			else if (value == "endDate") {
				this->setEndDate(stoi(panningValues[index]));
			}
			else if (value == "startHour") {
				this->setStartHour(stoi(panningValues[index]));
			}
			else if (value == "endHour") {
				this->setEndHour(stoi(panningValues[index]));
			}
		}
		index++;
	}
}