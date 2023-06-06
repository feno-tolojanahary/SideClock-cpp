#include <utility>
#include <set>
#include <ctime>
#include "TermGuiHyb.h"
#include "Helper.h"

void TermGuiHyb::printResume(const vector<TimeClock>& timeclocks, const vector<Planning>& plannings, const short& month, const int& year)
{
	vector<time_t> datesOfMonth = Helper::allDatesOfMonth(month, year);
	
	vector<vector<string>> lineOutputs;

	for (const time_t& dateOfMonth: datesOfMonth)
	{
		vector<string> lineOutput;
		for (const TimeClock& timeclock : timeclocks)
		{
			struct tm* tmStartTimeClock;
			struct tm* tmDateOfMonth = localtime(&dateOfMonth);
			time_t startTimeclock = timeclock.getStartDate();
			tmStartTimeClock = localtime(&startTimeclock);

			if (tmStartTimeClock->tm_year == tmDateOfMonth->tm_year
				&& tmStartTimeClock->tm_mon == tmDateOfMonth->tm_mon
				&& tmStartTimeClock->tm_wday == tmDateOfMonth->tm_wday)
			{
				char buffStartTimeClock[10], buffDateOfMonth[10];
				strftime(buffStartTimeClock, sizeof buffStartTimeClock, FORMAT_DATE, gmtime(&startTimeclock));
				strftime(buffDateOfMonth, sizeof buffDateOfMonth, FORMAT_DATE, gmtime(&dateOfMonth));
				lineOutput.push_back(buffStartTimeClock);
				lineOutput.push_back(buffDateOfMonth);

			}
		}
	}
}
