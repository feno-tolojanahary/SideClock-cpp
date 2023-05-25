#include "Storage.h"
#include "TimeClock.h"
#include "TermGui.h"

class ShiftManager {
public:
	void startTime();
	void stopTime();
	void listTime();

	~ShiftManager() {
		delete storage;
		delete termGui;
	}

private:
	Storage<TimeClock>* storage;
	TermGui<TimeClock>* termGui;
};
