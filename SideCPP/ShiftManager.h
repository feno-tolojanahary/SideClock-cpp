#include "Storage.h"
#include "TimeClock.h"

class ShiftManager {
public:
	void startTime();
	void stopTime();
	void listTime();

private:
	Storage<TimeClock>* storage;
};
