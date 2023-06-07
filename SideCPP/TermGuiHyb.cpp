#include "Helper.h"
#include <utility>
#include <ctime>
#include <map>
#include "TermGuiHyb.h"

template<class T>
bool TermGuiHyb::emplaceMatchValue(vector<string>* lineContent, const time_t& dateOfMonth, const T& elem)
{
	char buffStartDate[10];
	struct tm* tmElemDate;
	struct tm* tmDateOfMonth = localtime(&dateOfMonth);
	time_t startDate = elem.getStartDate();
	tmElemDate = localtime(&startDate);

	if (tmElemDate->tm_year == tmDateOfMonth->tm_year
		&& tmElemDate->tm_mon == tmDateOfMonth->tm_mon
		&& tmElemDate->tm_wday == tmDateOfMonth->tm_wday)
	{
		strftime(buffStartDate, sizeof buffStartDate, FORMAT_DATE, gmtime(&startDate));
		lineContent->push_back(buffStartDate);
		return true;
	}
	return false;
}

void TermGuiHyb::printResume(const vector<TimeClock>& timeclocks, const vector<Planning>& plannings, const short& month, const int& year)
{
	vector<time_t> datesOfMonth = Helper::allDatesOfMonth(month, year);
	
	map<string, vector<string>> lineOutputs;

	for (const time_t& dateOfMonth: datesOfMonth)
	{
		pair <string, vector<string>> line;
		vector<string> lineContent;
		char buffDateOfMonth[10], buffHourWorked[5];

		strftime(buffDateOfMonth, sizeof buffDateOfMonth, FORMAT_DATE, gmtime(&dateOfMonth));
		lineContent.push_back(buffDateOfMonth);

		for (const TimeClock& timeclock : timeclocks)
		{
			if (this->emplaceMatchValue<TimeClock>(&lineContent, dateOfMonth, timeclock)) break;
		}

		for (const Planning& planning : plannings)
		{
			if (this->emplaceMatchValue<Planning>(&lineContent, dateOfMonth, planning)) break;
		}


		lineOutputs.insert(line);
		line = make_pair(string(buffDateOfMonth), lineContent);
	}
}
