#include "TimeClock.h"
#include "Helper.h"


TimeClock::~TimeClock()
{

}

string TimeClock::getStrHeader() const
{
	stringstream sstr;
	sstr << "id" << DELIMITER << "startDate" << DELIMITER << "endDate" << DELIMITER << "owner" << endl;
	return sstr.str();
}

string TimeClock::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << startDate << DELIMITER << endDate << DELIMITER << owner << endl;
	return sstr.str();
}
