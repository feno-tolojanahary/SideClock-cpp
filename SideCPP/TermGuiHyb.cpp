#include <utility>
#include <set>
#include "TermGuiHyb.h"
#include "Helper.h"

void TermGuiHyb::printResume(const vector<TimeClock>& timeclocks, const vector<Planning>& plannings, const short& month, const int& year)
{
	vector<time_t> datesOfMonth = Helper::allDatesOfMonth(month, year);

}
