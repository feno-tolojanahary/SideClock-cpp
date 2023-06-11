#include "Helper.h"
#include <utility>
#include <ctime>
#include "TermGuiHyb.h"
#include "TermGui.h"

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
			Helper::emplaceMatchDateOnMonth<TimeClock>(&lineContent, dateOfMonth, timeclock);
		}

		for (const Planning& planning : plannings)
		{
			Helper::emplaceMatchDateOnMonth<Planning>(&lineContent, dateOfMonth, planning);
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
	vector<string> headers = Helper::splitChar(this->getStrHeader(), DELIMITER);

	termValOutputs.push_back(headers);

	for (const pair<string, vector<string>>& lineStructuredTerm : this->lineOutputs)
	{
		vector<string> termLineVal;
		termLineVal.push_back(lineStructuredTerm.first);

		for (const string& content : lineStructuredTerm.second)
		{
			termLineVal.push_back(content);
		}
		termValOutputs.push_back(termLineVal);
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

void TermGuiHyb::printPlanningList(const short& month, const int& year)
{
	vector<vector<string>> castedVals = Planning::castForOutput(plannings, month, year);
	TermGui<TermGuiHyb> termgui;
	string* printRes = &termgui.wrapStrResult(castedVals);
	cout << *printRes;
}