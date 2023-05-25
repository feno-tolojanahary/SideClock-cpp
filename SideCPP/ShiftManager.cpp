#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"

void ShiftManager::startTime()
{
	TimeClock timeclock(std::time(0), 1);
	storage->saveData(timeclock);
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
	}
}

void ShiftManager::listTime()
{
	vector<TimeClock> timeclockList = storage->listData(&parseTimeclock);

}