#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"
#include "TermGuiHyb.h"
#include "Planning.h"

void ShiftManager::startTime(const string& details)
{
	TimeClock timeclock;
	TimeClock existingTimeclock;
	storageTimeclock->findOneBy("endDate", 0, existingTimeclock);
	timeclock.startGui();
	if (existingTimeclock.getId() != -1)
	{
		return;
	}
	timeclock.setStartDate(std::time(0));
	timeclock.setDetails(details);
	storageTimeclock->saveData(timeclock);
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

void ShiftManager::planneHour(const string& strStartDate, const string& strEndDate, const string& strStartHour, const string& strEndHour)
{
	Planning planning(strStartDate, strEndDate, strStartHour, strEndHour);
	storagePlanning->findOneBy("startDate", Helper::stringToTime(strStartDate), planning);
	if (planning.getId() != -1)
	{
		cout << "Planning already exists." << endl;
		this->showCurrentPlannedList();
		return;
	}
	storagePlanning->saveData(planning);
	if (planning.getId() != -1)
	{
		cout << "Planning registered." << endl;
		this->showCurrentPlannedList();
	}
	else {
		cout << "Error when registering" << endl;
	}
}

void ShiftManager::showResume(const short& month, const int& year)
{
	int lastDayOfMonth = Helper::lastDayOfMonth(month, year);
	time_t startDate = Helper::createDate(1, month, year);
	time_t endDate = Helper::createDate(lastDayOfMonth, month, year);
	const string attrDate = "startDate";
	vector<TimeClock> timeclockList = storageTimeclock->findDateBetween(attrDate, startDate, endDate);
	vector<Planning> planningList = storagePlanning->findDateBetween(attrDate, startDate, endDate);
	TermGuiHyb termGuiHyb(timeclockList, planningList);
	termGuiHyb.setMonth(month);
	termGuiHyb.setYear(year);
	termGuiHyb.printResume();
}

void ShiftManager::showCurrentPlannedList()
{
	time_t currentDate;
	struct tm* tmDate, _tmDate;
	tmDate = &_tmDate;
	time(&currentDate);
	gmtime_s(tmDate, &currentDate);
	int lastDayOfMonth = Helper::lastDayOfMonth(tmDate->tm_mon, tmDate->tm_year);
	time_t startDate = Helper::createDate(1, tmDate->tm_mon, tmDate->tm_year);
	time_t endDate = Helper::createDate(lastDayOfMonth, tmDate->tm_mon, tmDate->tm_year);
	const string attrDate = "startDate";
	vector<Planning> planningList = storagePlanning->findDateBetween(attrDate, startDate, endDate);
	TermGuiHyb termGuiHyb(planningList);
	termGuiHyb.printPlanningList();
}

void ShiftManager::deletePlannedHour(const int& id)
{
	if (storageTimeclock->deleteById(id)) {
		cout << "Planned hour deleted with success" << endl;
	}
	else {
		cout << "No planned hour to delete" << endl;
	}
}

void ShiftManager::deletePlannedHour(const string& date)
{
	int deletedCount = storageTimeclock->deleteByDate("startDate", date);
	cout << deletedCount <<" deleted rows" << endl;
}

void ShiftManager::deletePlannedHour(const string& startDate, const string& endDate)
{
	int deletedCount = storageTimeclock->deleteBetweenADate("startDate", startDate, endDate);
	cout << deletedCount << " deleted rows" << endl;
}