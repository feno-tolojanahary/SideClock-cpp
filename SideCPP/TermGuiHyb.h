#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "TimeClock.h"
#include "Planning.h"
#include "ModelTermGui.h"

using namespace std;
class TermGuiHyb: public ModelTermGui
{
public:

	TermGuiHyb(vector<Planning> _plannings);

	TermGuiHyb(vector<TimeClock> _timeclocks, vector<Planning> _plannings);

private:
	vector<vector<vector<string>>> castForPrint() const;
	void printGroupedWeekData(vector<vector<vector<string>>> weekData) const;
	void processResume();
	void printTotalPlanTime() const;

	void initializeMonthYear();

public:
	
	string getStrHeader() const override;
	void printResume();
	void printPlanningList();

	void setMonth(short _month);

	void setYear(int _year);

private:
	map<string, vector<string>> lineOutputs{};
	vector<Planning> plannings{};
	vector<TimeClock> timeclocks{};
	short month;
	int year;
};

