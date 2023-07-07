#pragma once
#include "Storage.h"
#include "TermGui.h"
#include "TimeClock.h"
#include "Planning.h"

class ShiftManager {
private:
	void showCurrentPlannedList();

public:

	ShiftManager(): storageTimeclock(nullptr), termGui(nullptr)
	{
		const char* fileTimeclock = "timeclock";
		const char* filePlanning = "planning";
		this->storageTimeclock = new Storage<TimeClock>(fileTimeclock);
		this->storagePlanning = new Storage<Planning>(filePlanning);
		this->termGui = new TermGui<TimeClock>();
	}

	void startTime(const string& details);
	void stopTime();
	void planneHour(const string& strDate, const string& strEndDate, const string& startHour, const string& endHour);
	void showResume(const short& month, const int& year);

	~ShiftManager() {
		delete storageTimeclock;
		delete storagePlanning;
		delete termGui;
	}

private:
	Storage<TimeClock>* storageTimeclock;
	Storage<Planning>* storagePlanning;
	TermGui<TimeClock>* termGui;
};
