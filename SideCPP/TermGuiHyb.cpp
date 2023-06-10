#include "Helper.h"
#include <utility>
#include <ctime>
#include "TermGuiHyb.h"
#include "TermGui.h"

template<class T>
bool TermGuiHyb::emplaceMatchValue(vector<string>* lineContent, const time_t& dateOfMonth, const T& elem)
{
	struct tm* tmElemDate;
	struct tm* tmDateOfMonth = localtime(&dateOfMonth);
	time_t startDate = elem.getStartDate();
	tmElemDate = localtime(&startDate);

	if (tmElemDate->tm_year == tmDateOfMonth->tm_year
		&& tmElemDate->tm_mon == tmDateOfMonth->tm_mon
		&& tmElemDate->tm_wday == tmDateOfMonth->tm_wday)
	{
		lineContent->push_back(elem.getStrDate());
		return true;
	}
	return false;
}

void TermGuiHyb::processResume(const short& month, const int& year)
{
	vector<time_t> datesOfMonth = Helper::allDatesOfMonth(month, year);

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


		this->lineOutputs.insert(line);
		line = make_pair(string(buffDateOfMonth), lineContent);
	}
}

string TermGuiHyb::getStrHeader() const
{
	stringstream sstr;
	sstr << "Date" << DELIMITER << "Planned" << DELIMITER << "Worked\n";
	return sstr.str();
}

vector<vector<string>> TermGuiHyb::castForPrint() const
{
	vector<vector<string>> termValOutputs;

	for (const pair<string, vector<string>>& lineStructuredTerm : this->lineOutputs)
	{
		vector<string> termLineVal;
		termLineVal.push_back(lineStructuredTerm.first);

		for (const string& content : lineStructuredTerm.second)
		{
			termLineVal.push_back(content);
		}
	}

	return termValOutputs;
}

void TermGuiHyb::printResume(const short& month, const int& year)
{
	processResume(month, year);
	vector<vector<string>> castedVals = this->castForPrint();
	TermGui<TermGuiHyb> termgui;
	string* printRes = &termgui.wrapStrResult(castedVals);
	cout << *printRes;
}
