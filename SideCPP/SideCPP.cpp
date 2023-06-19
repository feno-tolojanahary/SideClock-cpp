#include <iostream>
#include <cstring>
#include "ShiftManager.h"
#include "Helper.h"

using namespace std;

void parseMonthYearVal(const int& index, char* argv[], short* month, int* year);
void parsePlanStartEnd(const int& index, char* argv[], string* strStartDate, string* strEndDate, string* strStartHour, string* strEndHour);

void parseAndAssignVal(const int& index, char* argv[], const string& argName, string* toStoreVal);

int main(int argc, char* argv[])
{
	if (argc > 1) 
	{
		if (strcmp(argv[1], "start") == 0) {

			string details = "";
			ShiftManager shiftManager;

			if (argc > 2)
			{
				parseAndAssignVal(2, argv, "--task", &details);
			}
			shiftManager.startTime(details);
		}
		else if (strcmp(argv[1], "stop") == 0)
		{
			ShiftManager shiftManager;
			shiftManager.stopTime();
		}
		else if (strcmp(argv[1], "list") == 0)
		{
			short month;
			int year;
			time_t currentTime;
			struct tm tmCurrent;
			ShiftManager shiftManager;

			time(&currentTime);
			gmtime_s(&tmCurrent, &currentTime);

			if (argc > 2)
			{
				parseMonthYearVal(2, argv, &month, &year);
				if (argc > 3)
				{
					parseMonthYearVal(3, argv, &month, &year);
				}
			}

			shiftManager.showResume(month, year);
		}
		else if (strcmp(argv[1], "plan") == 0)
		{
			string strStartDate, strEndDate, strStartHour, strEndHour;
			ShiftManager shiftManager;
			if (argc > 2)
			{
				parsePlanStartEnd(2, argv, &strStartDate, &strEndDate, &strStartHour, &strEndHour);
				if (argc > 3)
				{
					parsePlanStartEnd(3, argv, &strStartDate, &strEndDate, &strStartHour, &strEndHour);
					if (argc > 4)
					{
						parsePlanStartEnd(4, argv, &strStartDate, &strEndDate, &strStartHour, &strEndHour);
						if (argc > 5)
						{
							parsePlanStartEnd(5, argv, &strStartDate, &strEndDate, &strStartHour, &strEndHour);
						}
					}
				}

			}
			if (strStartDate.empty() || strEndDate.empty() || strStartHour.empty() || strEndHour.empty())
			{
				cout << "Argument not complete or a wrong spell in one of argument name \n";
				return 0;
			}
			else {
				shiftManager.planneHour(strStartDate, strEndDate, strStartHour, strEndHour);
			}
		}
	}
	else {
		cout << "start		 start time clock \n";
		cout << "stop		 stop time clock \n";
		cout << "list		 list time clock \n";
		cout << "plan		 plan time clock \n";
	}
}

void assignValueStrIfExist(const string* argvVal, const string& argName, string* toStoreVal);
void assignValueIntIfExist(const string* argVal, const string& argName, int* toStoreVal);

void parseAndAssignVal(const int& index, char* argv[], const string& argName, string* toStoreVal)
{
	string* argument = new string(argv[index]);
	assignValueStrIfExist(argument, argName, toStoreVal);
}

void parseMonthYearVal(const int& index, char* argv[], short* month, int* year)
{
	string* argument = new string(argv[index]);
	int convertedMonth = static_cast<int>(*month);
	assignValueIntIfExist(argument, "--month", &convertedMonth);
	assignValueIntIfExist(argument, "--year", year);
}

void parsePlanStartEnd(const int& index, char* argv[], string* strStartDate, string* strEndDate, string* strStartHour, string* strEndHour)
{
	string* argument = new string(argv[index]);
	assignValueStrIfExist(argument, "--startDate", strStartDate);
	assignValueStrIfExist(argument, "--endDate", strEndDate);
	assignValueStrIfExist(argument, "--startHour", strStartHour);
	assignValueStrIfExist(argument, "--endHour", strEndHour);
}

void assignValueStrIfExist(const string* argvVal, const string& argName, string* toStoreVal)
{
	if (argvVal->find(argName) != string::npos) {
		vector<string> splitedChar = Helper::splitChar(*argvVal, '=');
		toStoreVal = &splitedChar[2];
	}
}

void assignValueIntIfExist(const string* argVal, const string& argName, int* toStoreVal)
{
	if (argVal->find("--year") != string::npos)
	{
		vector<string> splitedChar = Helper::splitChar(*argVal, '=');
		int val = stoi(splitedChar[2]);
		toStoreVal = &val;
	}
}


