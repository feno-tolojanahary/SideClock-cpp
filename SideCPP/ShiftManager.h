#include "Storage.h"
#include "Head.h"	

class ShiftManager {
public:
	void startTime();
	void stopTime();
	void listTime();

private:
	Storage<TimeClock, TimeClockOpt>* storage;
};
