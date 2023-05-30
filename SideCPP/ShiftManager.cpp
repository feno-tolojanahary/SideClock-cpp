#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"

void ShiftManager::startTime()
{
	TimeClock timeclock;
	TimeClock existingTimeclock;
	storage->findOneBy("endDate", "0", existingTimeclock);
	if (existingTimeclock.getId() != -1)
	{
		timeclock.startGui();
		return;
	}
	timeclock.setStartDate(std::time(0));
	storage->saveData(timeclock);
	timeclock.startGui();
}

void ShiftManager::stopTime()
{
	TimeClock timeclock;
	storage->findOneBy("endDate", "0", timeclock);
	if (timeclock.getId() != -1) {
		TimeClock* timeclockOpt = new TimeClock(timeclock);
		time_t now = std::time(0);
		timeclockOpt->setEndDate(now);
		storage->updateById(timeclockOpt->getId(), *timeclockOpt);
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
	vector<TimeClock> timeclockList = storage->listData();
	termGui->print(timeclockList);
}