#include "ArgsParsing.h"

ArgsParsing::ArgsParsing(int argc, char* argv[])
{
	this->argc = argc;
	this->argv = argv;
}

void ArgsParsing::init()
{
	try {
		Args::CmdLine cmd(argc, argv, Args::CmdLine::CommandIsRequired);
		cmd.addCommand("start", Args::ValueOptions::NoValue, true, "Start timeclock", "Start tracking the timeclock")
			.addArgWithFlagAndName('t',  "task", true, false, "Description task")
			.end();
		cmd.addCommand("stop", Args::ValueOptions::NoValue, true, "Stop timeclock").end();
		cmd.addCommand("list", Args::ValueOptions::NoValue, true, "List registered timeclock")
			.addArgWithFlagAndName('m', "month", true, true, "Month of date")
			.addArgWithFlagAndName('y', "year", true, true, "Year of date")
			.end();
		cmd.addCommand("plan", Args::ValueOptions::NoValue, true, "Plan a timeclock")
			.addArgWithNameOnly("start-date", true, true, "Start date")
			.addArgWithNameOnly("end-date", true, true, "End date")
			.addArgWithNameOnly("start-hour", true, true, "Start hour")
			.addArgWithNameOnly("end-hour", true, true, "End hour")
			.addCommand("delete", Args::ValueOptions::NoValue, false, "Delete a planned timeclock")
			.end();
		cmd.parse();
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
}