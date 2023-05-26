#pragma once
#include "Storage.h"
#include "TermGui.h"
#include "TimeClock.h"

class ShiftManager {
public:

	ShiftManager(): storage(nullptr), termGui(nullptr)
	{
		const char* filename = "timeclock";
		this->storage = new Storage<TimeClock>(filename);
		this->termGui = new TermGui<TimeClock>();
	}

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
