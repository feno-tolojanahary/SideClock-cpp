#pragma once
#include <iostream>
#include <ctime>
#include "ModelStorage.h"

using namespace std;

class Planning: public ModelStorage
{
private:
	int id = -1;
	time_t startDate = 0;
	time_t endDate = 0;
	time_t startHour = 0;
	time_t endHour = 0;

public:

	Planning() {}

	Planning(time_t _startDate, time_t _endDate, time_t _startHour, time_t _endHour): 
		startDate(_startDate), endDate(_endDate), startHour(_startHour), endHour(_endHour) {}

	Planning(string strStartDate, string strEndDate, string strStartHour, string strEndHour);

	string getStrHeaderList() const;
	string stringify() const override;
	string strOutput() const override;
	string getStrDate() const override;
	void populateStr(const vector<string>& headers, const vector<string>& panningValues) override;

	int getDiffHour() const;


	static string getStrHeaderStorage();

	const string storageName() override
	{
		return "planningHour";
	}

	void setId(int _id) override
	{
		id = _id;
	}

	int getId() const override
	{
		return id;
	}

	void setStartDate(time_t date)
	{
		startDate = date;
	}

	time_t getStartDate() const
	{
		return startDate;
	}

	void setEndDate(time_t date)
	{
		endDate = date;
	}

	time_t getEndDate() const
	{
		return endDate;
	}

	void setStartHour(time_t hour)
	{
		startHour = hour;
	}

	time_t getStartHour() const
	{
		return startHour;
	}

	void setEndHour(time_t hour)
	{
		endHour = hour;
	}

	time_t getEndHour() const
	{
		return endHour;
	}

	static vector<vector<vector<string>>> castForOutput(vector<Planning> plannings, const short& month, const int& year);

};