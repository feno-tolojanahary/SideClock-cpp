#include "Storage.h"
#include "Head.h"	

class ShiftManager {
public:
	void startTime();
	void stopTime();

private:
	Storage<TimeClock, TimeClockOpt>* storage;
};
