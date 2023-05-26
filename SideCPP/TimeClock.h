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

	static void parse(const vector<string>& headers, const vector<string>& timeclockValues, TimeClock & timeclock)
	{
		int index = 0;
		for (const string& value : headers) {
			if (index < timeclockValues.size()) {
				if (value == "id") {
					timeclock.setId(stoi(timeclockValues[index]));
				}
				else if (value == "startDate") {
					timeclock.setStartDate(Helper::stringToTime(timeclockValues[index]));
				}
				else if (value == "endDate") {
					timeclock.setEndDate(Helper::stringToTime(timeclockValues[index]));
				}
				else if (value == "owner") {
					timeclock.setOwner(stoi(timeclockValues[index]));
				}
			}
			index++;
		}
	}
};