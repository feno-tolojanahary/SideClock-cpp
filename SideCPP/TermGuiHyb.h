#pragma once
#include <iostream>
#include <vector>
#include "TimeClock.h"
#include "Planning.h"

using namespace std;
class TermGuiHyb
{
public:
	
	void printResume(const vector<TimeClock>& timeclocks, const vector<Planning>& plannings, const short& month, const int& year);
};