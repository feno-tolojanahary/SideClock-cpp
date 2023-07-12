#include <iostream>
#include <cstring>
#include "ShiftManager.h"
#include "Helper.h"
#include "lib/args-parser-master/args-parser/all.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	try {
		Args::CmdLine cmd(argc, argv, Args::CmdLine::CommandIsRequired);
		cmd.addCommand("start", Args::ValueOptions::NoValue, true, "Start timeclock", "Start tracking the timeclock")
			.addArgWithFlagAndName('t', "task", true, false, "Description task")
			.end();
		cmd.addCommand("stop", Args::ValueOptions::NoValue, true, "Stop timeclock").end();
		cmd.addCommand("list", Args::ValueOptions::NoValue, true, "List registered timeclock")
			.addArgWithFlagAndName('m', "month", true, false, "Month of date")
			.addArgWithFlagAndName('y', "year", true, false, "Year of date")
			.end();
		cmd.addCommand("plan", Args::ValueOptions::NoValue, true, "Plan a timeclock")
			.addArgWithNameOnly("start-date", true, true, "Start date")
			.addArgWithNameOnly("end-date", true, true, "End date")
			.addArgWithNameOnly("start-hour", true, true, "Start hour")
			.addArgWithNameOnly("end-hour", true, true, "End hour")
			.addArgWithFlagAndName('l', "list", false, false, "List planned hours")
			.end()
			.addCommand("plan", Args::ValueOptions::NoValue, true, "Plan a timeclock")
			.addCommand("delete", Args::ValueOptions::NoValue, false, "Delete a planned timeclock")
			.addArgWithNameOnly("id", true, false, "Id of timeclock to delete", "Specify an id of timeclock to delete in the list")
			.addArgWithNameOnly("date", true, false, "Point out a special date to delete")
			.addArgWithNameOnly("start-date", true, false, "Specify a start of date")
			.addArgWithNameOnly("end-date", true, false, "Specify an end of date")
			.end()
			.end();

		cmd.parse();

		ShiftManager shiftManager;
		if (cmd.isDefined("start")) {
			string details = "";
			if (cmd.isDefined("-t"))
				details = cmd.value("-t");
			shiftManager.startTime(details);
		}
		if (cmd.isDefined("stop")) {
			shiftManager.stopTime();
		}
		if (cmd.isDefined("list")) {
			string month;
			string year;
			time_t currentTime;
			struct tm tmCurrent;

			time(&currentTime);
			gmtime_s(&tmCurrent, &currentTime);
			month = to_string(tmCurrent.tm_mon);
			year = to_string(tmCurrent.tm_year);

			if (cmd.isDefined("-m"))
				month = cmd.value("-m");
			if (cmd.isDefined("-y"))
				year = cmd.value("-y");

			shiftManager.showResume(stoi(month), stoi(year));
		}
		if (cmd.isDefined("plan")) {
			if (cmd.isDefined("-l")) {
				shiftManager.showCurrentPlannedList();
			}
			if (cmd.isDefined("delete")) {

			}
			else {
				string strStartDate, strEndDate, strStartHour, strEndHour;
				strStartDate = cmd.value("--start-date");
				strEndDate = cmd.value("--end-date");
				strStartHour = cmd.value("--start-hour");
				strEndHour = cmd.value("--end-hour");
				shiftManager.planneHour(strStartDate, strEndDate, strStartHour, strEndHour);
			}
		}
	}
	catch (const Args::HelpHasBeenPrintedException&) {
		cout << "Error arguments" << endl;
		return 0;
	}
	catch (const Args::BaseException& x)
	{
		Args::outStream() << x.desc() << "\n";

		return 0;
	}
	return 1;
}

