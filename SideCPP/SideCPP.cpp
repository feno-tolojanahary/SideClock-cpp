#include <iostream>
#include "ShiftManager.h"

int main(int argc, char* argv[])
{
	if (argv[1] == "--start")
	{
		ShiftManager shiftManager;
		shiftManager.startTime();
	}
	else if (argv[1] == "--stop")
	{
		ShiftManager shiftManager;
		shiftManager.stopTime();
	}
	else if (argv[1] == "--list")
	{
		ShiftManager shiftManager;
		shiftManager.listTime();
	}
	else {
		cout << "--start	 start time clock \n";
		cout << "--stop		 stop time clock \n";
		cout << "--list		 list time clock \n";
	}
}



