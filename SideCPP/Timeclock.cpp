#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include "TimeClock.h"
#include "Helper.h"


TimeClock::~TimeClock()
{

}

tm* TimeClock::getTimeDiff()
{
	time_t diff = difftime(endDate, startDate);
	return gmtime(&diff);
}

string TimeClock::getStrHeader() const
{
	stringstream sstr;
	sstr << "id" << DELIMITER << "startDate" << DELIMITER << "endDate" << DELIMITER << "owner\n";
	return sstr.str();
}

string TimeClock::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << startDate << DELIMITER << endDate << DELIMITER << to_string(owner) + "\n";
	return sstr.str();
}

void TimeClock::populateStr(const vector<string>& headers, const vector<string>& timeclockValues)
{
	int index = 0;
	for (const string& value : headers) {
		if (index < timeclockValues.size()) {
			if (value == "id") {
				this->setId(stoi(timeclockValues[index]));
			}
			else if (value == "startDate") {
				this->setStartDate(stoi(timeclockValues[index]));
			}
			else if (value == "endDate") {
				this->setEndDate(stoi(timeclockValues[index]));
			}
			else if (value == "owner") {
				this->setOwner(stoi(timeclockValues[index]));
			}
		}
		index++;
	}
}

void TimeClock::displayTimer(const tm* timer) 
{
	system("cls");
	cout << setfill(' ') << setw(55) << " --------------------------\n";
	cout << setfill(' ') << setw(37);
	cout << "|         " << setfill('0') << setw(2) << timer->tm_hour << ":";
	cout << setfill('0') << setw(2) << timer->tm_min << ":";
	cout << setfill('0') << setw(2) << timer->tm_sec << "         |" << endl;
	cout << setfill(' ') << setw(55) << " --------------------------\n";
}

void TimeClock::startGui()
{
	while (true) {
		tm* timer = this->getTimeDiff();
		this->displayTimer(timer);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

string TimeClock::strOutput() const
{
	stringstream sstr;
	char buffStart[16], buffEnd[16];
	strftime(buffStart, sizeof buffStart, FORMAT_DATE_HOUR, gmtime(&startDate));
	if (endDate > 0)
	{
		strftime(buffEnd, sizeof buffEnd, FORMAT_DATE_HOUR, gmtime(&endDate));
	}
	sstr << id << DELIMITER << buffStart << DELIMITER << buffEnd << DELIMITER << to_string(owner) + "\n";
	return sstr.str();
}
