#include "ShiftManager.h"

void ShiftManager::startTime()
{
	TimeClock* timeclock = nullptr;
	timeclock->startDate = std::time(0);
	storage->saveData(*timeclock, &stringifyTimeclock);
}

void ShiftManager::stopTime()
{

}