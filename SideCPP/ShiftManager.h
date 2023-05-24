#include "Storage.h"

class ShiftManager {
public:
	void startTime();
	void stopTime();
	void listTime();

private:
	Storage<TimeClock, TimeClockOpt>* storage;
};
