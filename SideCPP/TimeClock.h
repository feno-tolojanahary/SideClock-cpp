#pragma once
#include <ctime>
#include "ModelStorage.h"

class TimeClock: public ModelStorage
{

private:
	int id = -1;
	int owner = 1;
	time_t startDate = 0;
	time_t endDate = 0;

public:

	~TimeClock();

	string getStrHeader() const override;
	string stringify() const override;

	void setStartDate(time_t startDate) 
	{ 
		this->startDate = startDate; 
	}

	void setEndDate(time_t endDate) 
	{
		this->endDate = endDate;
	}

	void setOwner(int owner)
	{
		this->owner = owner;
	}

	void setId(int id) override 
	{
		this->id = id;
	}

	int getId() const override
	{
		return id;
	}

	int getOwner() const
	{
		return owner;
	}

	time_t getEndDate() const
	{
		return endDate;
	}

	time_t getStartDate() const
	{
		return startDate;
	}

	void populateStr(const vector<string>& headers, const vector<string>& timeclockValues) override;
};