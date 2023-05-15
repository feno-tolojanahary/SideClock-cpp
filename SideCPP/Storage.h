#include <fstream>
#include <vector>

using namespace std;

template <class T>
class Storage {

public: 

	Storage(char * fileName): filename(fileName) {}

	T saveData(T& data, function<std::string(T)> toStr);
	vector<string> readData();
	T findByCondition(std::string attr, auto value);

private:
	int getLineCount();

	char * filename;
	fstream file;
};