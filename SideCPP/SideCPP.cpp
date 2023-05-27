#include <iostream>
#include <cstring>
#include "ShiftManager.h"

using namespace std;

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
			ShiftManager shiftManager;
			shiftManager.listTime();
		}
	}
	else {
		cout << "--start	 start time clock \n";
		cout << "--stop		 stop time clock \n";
		cout << "--list		 list time clock \n";
	}
}



