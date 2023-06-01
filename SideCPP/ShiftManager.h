#pragma once
#include "Storage.h"
#include "TermGui.h"
#include "TermGuiHyb.h"
#include "TimeClock.h"
#include "Planning.h"

class ShiftManager {
public:

	ShiftManager(): storageTimeclock(nullptr), termGui(nullptr)
	{
		const char* fileTimeclock = "timeclock";
		const char* filePlanning = "planning";
		this->storageTimeclock = new Storage<TimeClock>(fileTimeclock);
		this->storagePlanning = new Storage<Planning>(filePlanning);
		this->termGui = new TermGui<TimeClock>();
		this->termGuiHyb = new TermGuiHyb();
	}

	void startTime();
	void stopTime();
	void listTime();
	void plannedHour(const string& strDate, const string& strEndDate, const string& startHour, const string& endHour);
	void showResume();

	~ShiftManager() {
		delete storageTimeclock;
		delete storagePlanning;
		delete termGui;
	}

private:
	Storage<TimeClock>* storageTimeclock;
	Storage<Planning>* storagePlanning;
	TermGui<TimeClock>* termGui;
	TermGuiHyb* termGuiHyb;
};
