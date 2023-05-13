#include "ShiftManager.h"
#include "Head.h"

void ShiftManager::startTime()
{
	TimeClock* timeclock;
	timeclock->startDate = std::time(0);
	storage->saveData(timeclock);
}

void ShiftManager::stopTime()
{

}