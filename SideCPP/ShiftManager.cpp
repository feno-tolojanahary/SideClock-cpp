#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"
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

void ShiftManager::listTime()
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

void ShiftManager::showResume(const string& strStartDate, const string& strEndDate)
{
	const string attrDate = "startDate";
	vector<TimeClock> timeclockList = storageTimeclock->findDateBetween(attrDate, strStartDate, strEndDate);
	vector<Planning> planningList = storagePlanning->findDateBetween(attrDate, strStartDate, strEndDate);
	termGuiHyb->printResume(timeclockList, planningList);

}
