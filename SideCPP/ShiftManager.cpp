#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"

void ShiftManager::startTime()
{
	TimeClock timeclock;
	timeclock.setStartDate(std::time(0));
	storage->saveData(timeclock);
	cout << "Timeclock starting..." << endl;
}

void ShiftManager::stopTime()
{
	TimeClock timeclock;
	storage->findOneBy("startDate", "0", TimeClock::parse, timeclock);
	if (timeclock.getId()) {
		TimeClock* timeclockOpt = new TimeClock(timeclock);
		time_t now = std::time(0);
		timeclockOpt->setEndDate(now);
		storage->updateById(timeclockOpt->getId(), TimeClock::parse, *timeclockOpt);
		delete timeclockOpt;
	}
	cout << "Timeclock stopped." << endl;
}

void ShiftManager::listTime()
{
	vector<TimeClock> timeclockList = storage->listData(TimeClock::parse);
	termGui->print(timeclockList);
}