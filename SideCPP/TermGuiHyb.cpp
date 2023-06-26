#include <utility>
#include <ctime>
#include <cmath>
#include <sstream>
#include "TermGuiHyb.h"
#include "TermGui.h"
#include "Helper.h"

TermGuiHyb::TermGuiHyb(vector<Planning> _plannings)
{
	plannings = _plannings;
	this->initializeMonthYear();
}

TermGuiHyb::TermGuiHyb(vector<TimeClock> _timeclocks, vector<Planning> _plannings)
{
	timeclocks = _timeclocks;
	plannings = _plannings;
	this->initializeMonthYear();
}

void TermGuiHyb::initializeMonthYear()
{
	struct tm tmCurrentDate;
	time_t currentTime = time(0);
	localtime_s(&tmCurrentDate, &currentTime);
	month = tmCurrentDate.tm_mon + 1;
	year = tmCurrentDate.tm_year + 1900;
}

void TermGuiHyb::setMonth(short _month)
{
	month = _month;
}

void TermGuiHyb::setYear(int _year)
{
	year = _year;
}

void TermGuiHyb::processResume()
{
	vector<time_t> datesOfMonth = Helper::allDatesOfMonth(month, year);

	for (const time_t& dateOfMonth: datesOfMonth)
	{
		pair <string, vector<string>> line;
		vector<string> lineContent;
		struct tm tmDateOfMonth;
		char buffDateOfMonth[11];
		
		localtime_s(&tmDateOfMonth, &dateOfMonth);

		strftime(buffDateOfMonth, sizeof buffDateOfMonth, FORMAT_DATE, &tmDateOfMonth);
		lineContent.push_back(buffDateOfMonth);

		for (const TimeClock& timeclock : timeclocks)
		{
			Helper::emplaceMatchDateOnMonth<TimeClock>(&lineContent, dateOfMonth, timeclock);
		}

		for (const Planning& planning : plannings)
		{
			Helper::emplaceMatchDateOnMonth<Planning>(&lineContent, dateOfMonth, planning);
		}

		line = make_pair(string(buffDateOfMonth), lineContent);
		this->lineOutputs.insert(line);
	}
}

string TermGuiHyb::getStrHeader() const
{
	stringstream sstr;
	sstr << "Date" << DELIMITER << "Planned" << DELIMITER << "Worked\n";
	return sstr.str();
}

vector<vector<vector<string>>> TermGuiHyb::castForPrint() const
{
	const short columnNumberOutput = 3;
	const short	weekNumberMonth = Helper::getWeekNumber(month, year);
	vector<string> headers = Helper::splitChar(this->getStrHeader(), DELIMITER);
	vector<vector<string>> defaultWeekOutput(1, headers);
	vector<vector<vector<string>>> termValOutputs(weekNumberMonth, defaultWeekOutput);
	
	int firstWeekOfYearInMonth = 0;

	for (const pair<string, vector<string>>& lineStructuredTerm : this->lineOutputs)
	{
		int weekOfMonthIndex = 0;
		int weekOfYear = 0;
		vector<string> lineData;

		struct tm tmLineDate;
		memset(&tmLineDate, 0, sizeof(tmLineDate));
		istringstream iss(lineStructuredTerm.first);
		iss >> get_time(&tmLineDate, FORMAT_DATE);

		mktime(&tmLineDate);

		char buffWeekOfYear[3];
		strftime(buffWeekOfYear, sizeof buffWeekOfYear, "%W", &tmLineDate);
		weekOfYear = stoi(buffWeekOfYear);
		
		if (tmLineDate.tm_mday == 1) {
			firstWeekOfYearInMonth = weekOfYear;
		}

		weekOfMonthIndex = weekOfYear - firstWeekOfYearInMonth;

		lineData.push_back(lineStructuredTerm.first);
		for (const string& content : lineStructuredTerm.second)
		{
			lineData.push_back(content);
		}
		vector<vector<string>> weekOutput = termValOutputs.at(weekOfMonthIndex);
		weekOutput.push_back(lineData);
		termValOutputs.at(weekOfMonthIndex) = weekOutput;
	}

	return termValOutputs;
}

void TermGuiHyb::printTotalPlanTime() const
{
	int planningTotalHour = 0, timeclockTotalHour = 0;
	vector<vector<string>> totalOut;
	TermGui<TermGuiHyb> termgui;
	stringstream ssout;

	for (const Planning& planning : plannings)
	{
		planningTotalHour += planning.getDiffHour();
	}

	for (const TimeClock& timeclock : timeclocks)
	{
		timeclockTotalHour += timeclock.getDiffHour();
	}

	vector<string> headers{"Planned", "Worked"};
	vector<string> total;
	total.push_back(to_string(planningTotalHour));
	total.push_back(to_string(timeclockTotalHour));
	totalOut.push_back(headers);
	totalOut.push_back(total);

	ssout << "Total Month \n";
	termgui.wrapStrResult(totalOut, totalOut.size(), ssout);
	cout << ssout.str();
}

void TermGuiHyb::printGroupedWeekData(vector<vector<vector<string>>> weekData) const
{
	TermGui<TermGuiHyb> termgui;
	int weekIndex = 1;
	stringstream ssout;

	for (const vector<vector<string>> weekCastedVal : weekData) 
	{
		ssout << "Week " + to_string(weekIndex) + "\n";
		termgui.wrapStrResult(weekCastedVal, weekCastedVal.size(), ssout);
		ssout << "\n\n";
		weekIndex++;
	}
	cout << ssout.str();
}

void TermGuiHyb::printResume()
{
	processResume();
	vector<vector<vector<string>>> castedVals = this->castForPrint();
	this->printGroupedWeekData(castedVals);
	this->printTotalPlanTime();
}

void TermGuiHyb::printPlanningList()
{
	vector<vector<vector<string>>> castedVals = Planning::castForOutput(plannings, month, year);
	TermGui<TermGuiHyb> termgui;
	this->printGroupedWeekData(castedVals);
}