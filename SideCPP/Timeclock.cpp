#include "TimeClock.h"


TimeClock::~TimeClock()
{

}

string TimeClock::getStrHeader() const
{
	string separator = (string)DELIMITER;
	return "id" + separator + "startDate" + separator + "endDate" + separator + "owner";
}

string TimeClock::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << startDate << DELIMITER << endDate << DELIMITER << owner << endl;
	return sstr.str();
}
