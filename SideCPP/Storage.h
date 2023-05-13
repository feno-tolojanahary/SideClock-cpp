#include <iostream>
#include <vector>

using namespace std;

class Storage {

public: 
	void saveData(const string & data);
	vector<string> readData();

private:
	char * filename;
	fstream file;
};