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
			.addCommand("delete", Args::ValueOptions::NoValue, false, "Delete a planned timeclock")
			.end();
		cmd.parse();

		if (cmd.isDefined("start")) {
			ShiftManager shiftManager;
			string details = "";
			if (cmd.isDefined("-t"))
				details = cmd.value("-t");
			shiftManager.startTime(details);
		}
		if (cmd.isDefined("stop")) {
			ShiftManager shiftManager;
			shiftManager.stopTime();
		}
		if (cmd.isDefined("list")) {
			string month;
			string year;
			time_t currentTime;
			struct tm tmCurrent;
			ShiftManager shiftManager;

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
			string strStartDate, strEndDate, strStartHour, strEndHour;
			ShiftManager shiftManager;
			strStartDate = cmd.value("--start-date");
			strEndDate = cmd.value("--end-date");
			strStartHour = cmd.value("--start-hour");
			strEndHour = cmd.value("--end-hour");
			shiftManager.planneHour(strStartDate, strEndDate, strStartHour, strEndHour);
		}
	}
	catch (const Args::HelpHasBeenPrintedException&) {
		cout << "Error arguments" << endl;
		return;
	}
	catch (const Args::BaseException& x)
	{
		Args::outStream() << x.desc() << "\n";

		return;
	}
	return 1;
}

