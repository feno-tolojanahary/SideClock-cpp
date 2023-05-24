#include <vector>
#include "ShiftManager.h"
#include "TermGui.h"

void ShiftManager::startTime()
{
	TimeClock* timeclock, tmc;
	timeclock = &tmc;
	timeclock->startDate = std::time(0);
	storage->saveData(*timeclock, &stringifyTimeclock);
}

void ShiftManager::stopTime()
{
	auto timeclock = storage->findOneBy("startDate", "0", &parseTimeclock);
	if (timeclock && timeclock->id) {
		TimeClockOpt timeclockOpt;
		timeclockOpt.startDate = timeclock->startDate;
		time_t now = std::time(0);
		timeclockOpt.endDate = now;
		timeclockOpt.owner = timeclock->owner;
		storage->updateById(timeclock->id, timeclockOpt, &stringifyTimeclock, &parseTimeclock);
	}
}

void ShiftManager::listTime()
{
	vector<TimeClock> timeclockList = storage->listData(&parseTimeclock);

}