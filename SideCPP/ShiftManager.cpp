#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"
#include "TermGuiHyb.h"
#include "Planning.h"

void ShiftManager::startTime()
{
	TimeClock timeclock;
	TimeClock existingTimeclock;
	storageTimeclock->findOneBy("endDate", 0, existingTimeclock);
	if (existingTimeclock.getId() != -1)
	{
		timeclock.startGui();
		return;
	}
	timeclock.setStartDate(std::time(0));
	storageTimeclock->saveData(timeclock);
	timeclock.startGui();
}

void ShiftManager::stopTime()
{
	TimeClock timeclock;
	storageTimeclock->findOneBy("endDate", 0, timeclock);
	if (timeclock.getId() != -1) {
		TimeClock* timeclockOpt = new TimeClock(timeclock);
		time_t now = std::time(0);
		timeclockOpt->setEndDate(now);
		storageTimeclock->updateById(timeclockOpt->getId(), *timeclockOpt);
		delete timeclockOpt;

		cout << "Timeclock stopped." << endl;
	}
	else
	{
		cout << "Timeclock not started" << endl;
	}
}

void ShiftManager::listTime(const short& month, const int& year)
{
	vector<TimeClock> timeclockList = storageTimeclock->listData();
	termGui->print(timeclockList);
}

void ShiftManager::plannedHour(const string& strStartDate, const string& strEndDate, const string& strStartHour, const string& strEndHour)
{
	Planning planning(strStartDate, strEndDate, strStartHour, strEndHour);
	storagePlanning->findOneBy("startDate", Helper::stringToTime(strStartDate), planning);
	if (planning.getId() != -1)
	{
		cout << "Planning already exists." << endl;
		return;
	}
	storagePlanning->saveData(planning);
	if (planning.getId() != -1)
	{
		cout << "Planning registered." << endl;
	}
	else {
		cout << "Error when registering" << endl;
	}
}

void ShiftManager::showResume(const string& strMonth, const string& strYear)
{
	short month = stoi(strMonth);
	int year = stoi(strYear);
	int lastDayOfMonth = Helper::lastDayOfMonth(month, year);
	time_t startDate = Helper::createDate(1, month, year);
	time_t endDate = Helper::createDate(lastDayOfMonth, month, year);
	const string attrDate = "startDate";
	vector<TimeClock> timeclockList = storageTimeclock->findDateBetween(attrDate, startDate, endDate);
	vector<Planning> planningList = storagePlanning->findDateBetween(attrDate, startDate, endDate);


}
