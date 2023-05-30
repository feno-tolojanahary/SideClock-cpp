#pragma once
#include <iostream>
#include <ctime>
#include "ModelStorage.h"

using namespace std;

class Planning: public ModelStorage
{
private:
	int id = -1;
	time_t date = 0;
	time_t plannedHour = 0;

public:

	string getStrHeader() const override;
	string stringify() const override;
	string strOutput() const override;
	void populateStr(const vector<string>& headers, const vector<string>& panningValues) override;

	void setId(int _id)
	{
		id = _id;
	}

	int getId() const
	{
		return id;
	}

	void setDate(time_t _date)
	{
		date = _date;
	}

	time_t getDate() const
	{
		return date;
	}

	void setPlannedHour(time_t hour)
	{
		plannedHour = hour;
	}
};