#pragma once
#include "Storage.h"
#include "TermGui.h"
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
	}

	void startTime(const string& details);
	void stopTime();
	void planneHour(const string& strDate, const string& strEndDate, const string& startHour, const string& endHour);
	void showResume(const short& month, const int& year);
	void showCurrentPlannedList();
	void deletePlannedHour(const int& id);
	void deletePlannedHour(const string& date);
	void deletePlannedHour(const string& startDate, const string& endDate);

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
