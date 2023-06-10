#include <iostream>
#include <cstring>
#include "ShiftManager.h"
#include "Helper.h"

using namespace std;

void parseMonthYearVal(const int& index, char* argv[], short* month, int* year);

int main(int argc, char* argv[])
{
	if (argc > 1) 
	{
		if (strcmp(argv[1], "--start") == 0)
		{
			ShiftManager shiftManager;
			shiftManager.startTime();
		}
		else if (strcmp(argv[1], "--stop") == 0)
		{
			ShiftManager shiftManager;
			shiftManager.stopTime();
		}
		else if (strcmp(argv[1], "--list") == 0)
		{
			short* month;
			int* year;
			time_t currentTime;
			struct tm* tmCurrent;
			ShiftManager shiftManager;

			time(&currentTime);
			tmCurrent = gmtime(&currentTime);

			if (argc > 2)
			{
				parseMonthYearVal(2, argv, month, year);
				if (argc > 3)
				{
					parseMonthYearVal(3, argv, month, year);
				}
			}

			shiftManager.listTime(*month, *year);
		}
		else if (strcmp(argv[1], "--plan") == 0)
		{
			
		}
	}
	else {
		cout << "--start	 start time clock \n";
		cout << "--stop		 stop time clock \n";
		cout << "--list		 list time clock \n";
	}
}

void parseMonthYearVal(const int& index, char* argv[], short* month, int* year)
{
	string* argument = new string(argv[index]);
	if (argument->find("--month") != string::npos)
	{
		vector<string> splitedChar = Helper::splitChar(*argument, '=');
		short monthVal = stoi(splitedChar[2]);
		month = &monthVal;
	}
	if (argument->find("--year") != string::npos)
	{
		vector<string> splitedChar = Helper::splitChar(*argument, '=');
		int yearVal = stoi(splitedChar[2]);
		year = &yearVal;
	}
}


