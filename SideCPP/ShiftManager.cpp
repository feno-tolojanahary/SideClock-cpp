#include "ShiftManager.h"
#include "Head.h"

void ShiftManager::startTime()
{
	TimeClock* timeclock;
	timeclock->startDate = std::time(0);
	storage->saveData(stringifyTimeclock(*timeclock));
}

void ShiftManager::stopTime()
{

}