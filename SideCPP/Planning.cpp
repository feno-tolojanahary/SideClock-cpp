#include <string>
#include "Planning.h"
#include "Helper.h"

string Planning::getStrHeader() const
{
	stringstream sstr;
	sstr << "id" << DELIMITER << "date" << DELIMITER << "plannedHour\n";
	return sstr.str();
}

string Planning::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << date << DELIMITER << plannedHour + "\n";
	return sstr.str();
}

string Planning::strOutput() const
{
	stringstream sstr;
	string _date, _plannedHour;
	char buffDate[70];
	struct tm* tmPlanned;
	strftime(buffDate, sizeof buffDate, "%A %c", gmtime(&date));
	_date.assign(buffDate);
	tmPlanned = gmtime(&plannedHour);
	_plannedHour = tmPlanned->tm_hour + ":" + tmPlanned->tm_min;
	sstr << id << DELIMITER << _date << DELIMITER << _plannedHour + "\n";
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
			else if (value == "date") {
				this->setDate(stoi(panningValues[index]));
			}
			else if (value == "planningHour") {
				this->setPlannedHour(stoi(panningValues[index]));
			}
		}
		index++;
	}
}