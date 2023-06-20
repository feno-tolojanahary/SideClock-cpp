#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include "TimeClock.h"
#include "Helper.h"


TimeClock::~TimeClock(){}

tm TimeClock::getTimeDiff()
{
	struct tm tmDiff;
	time_t diff = difftime(endDate, startDate);
	gmtime_s(&tmDiff, &diff);
	return tmDiff;
}

string TimeClock::getStrHeaderStorage()
{
	stringstream sstr;
	sstr << "id" << DELIMITER << "startDate" << DELIMITER << "endDate" << DELIMITER << "owner" << DELIMITER << "details\n";
	return sstr.str();
}

string TimeClock::getStrDate() const
{
	if (endDate == 0)
	{
		return "in progress...";
	}
	return Helper::hourMinutesStrDiff(endDate, startDate);
}

int TimeClock::getDiffHour() const
{
	double diffTime = difftime(endDate, startDate);
	return diffTime / 3600;
}

string TimeClock::stringify() const
{
	stringstream sstr;
	sstr << id << DELIMITER << startDate << DELIMITER << endDate << DELIMITER << to_string(owner) << DELIMITER << details + "\n";
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
			else if (value == "details") {
				this->setDetails(timeclockValues[index]);
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
		struct tm timer = this->getTimeDiff();
		this->displayTimer(&timer);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

string TimeClock::strOutput() const
{
	stringstream sstr;
	char buffStart[16], buffEnd[16];
	struct tm tmStartDate, tmEndDate;

	gmtime_s(&tmStartDate, &startDate);
	gmtime_s(&tmEndDate, &endDate);
	strftime(buffStart, sizeof buffStart, FORMAT_DATE_HOUR, &tmStartDate);
	if (endDate > 0)
	{
		strftime(buffEnd, sizeof buffEnd, FORMAT_DATE_HOUR, &tmEndDate);
	}
	sstr << id << DELIMITER << buffStart << DELIMITER << buffEnd << DELIMITER << to_string(owner) + "\n";
	return sstr.str();
}
