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
	TermGuiHyb(vector<TimeClock> _timeclocks, vector<Planning> _plannings)
	{
		timeclocks = _timeclocks;
		plannings = _plannings;
	}

private:
	template <class T>
	bool emplaceMatchValue(vector<string>* lineContent, const time_t& dateOfMonth, const T& elem);
	vector<vector<string>> castForPrint() const;
	void processResume(const short& month, const int& year);

public:
	
	string getStrHeader() const override;
	void printResume(const short& month, const int& year);

private:
	map<string, vector<string>> lineOutputs;
	vector<Planning> plannings;
	vector<TimeClock> timeclocks;
};

