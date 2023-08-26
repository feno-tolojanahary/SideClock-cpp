#pragma once
#include "Storage/Storage.h"
#include "TermGui.h"
#include "TimeClock.h"
#include "Planning.h"

class ShiftManager {
public:

	ShiftManager(): storageTimeclock(nullptr), termGui(nullptr)
	{
		const char* fileTimeclock = "timeclock";
		const char* filePlanning = "planning";
		storageTimeclock = std::make_shared<Storage<TimeClock>>(fileTimeclock);
		storagePlanning = std::make_shared<Storage<Planning>>(filePlanning);
		termGui = new TermGui<TimeClock>();
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
		delete termGui;
	}

private:
	std::shared_ptr<Storage<TimeClock>> storageTimeclock;
	std::shared_ptr<Storage<Planning>> storagePlanning;
	TermGui<TimeClock>* termGui;
};
