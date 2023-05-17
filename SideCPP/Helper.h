#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
class Helper {

public: 

	static vector<string> splitChar(char* lineChar, char separator)
	{
		vector<string> spliteStr;
		string tempStr;
		int i = 0;
		while (lineChar[i] != '\0') {
			if (lineChar[i] != separator) {
				tempStr += lineChar;
			}
			else {
				spliteStr.push_back(tempStr);
			}
			i++;
		}
		return spliteStr;
	}

	static time_t stringToTime(string timeStr) {
		struct tm tm;
		istringstream isstr(timeStr);
		isstr >> get_time(&tm, "%a %b %d %H:%M:%S %Y");
		time_t t = mktime(&tm);
		return t;
	}
};