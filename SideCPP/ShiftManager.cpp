#include "ShiftManager.h"

void ShiftManager::startTime()
{
	TimeClock* timeclock, tmc;
	timeclock = &tmc;
	timeclock->startDate = std::time(0);
	storage->saveData(*timeclock, &stringifyTimeclock);
}

void ShiftManager::stopTime()
{
	auto timeclock = storage->findOneBy("startDate", "", &parseTimeclock);
	if (timeclock && timeclock->id) {
		
	}
}