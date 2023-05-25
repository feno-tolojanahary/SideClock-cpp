#include <ctime>
#include "ModelStorage.h"

class TimeClock: public ModelStorage<TimeClock>
{

private:
	int id;
	int owner = 1;
	time_t startDate = 0;
	time_t endDate = 0;

public:
	
	TimeClock(time_t _startDate, time_t _endDate, int _owner, int _id)
			: startDate(_startDate), endDate(_endDate), owner(_owner), id(_id) {};


	TimeClock(time_t _startDate, time_t _endDate, int _owner)
		: startDate(_startDate), endDate(_endDate), owner(_owner) {};

	TimeClock(time_t _startDate, int _owner)
		: startDate(_startDate), owner(_owner) {};

	TimeClock() {};

	~TimeClock();

	string getStrHeader() const;
	string stringify() const;

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

	void setId(int id)
	{
		this->id = id;
	}

	int getId() const
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