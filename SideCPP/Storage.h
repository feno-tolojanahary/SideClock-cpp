#include <fstream>
#include <vector>
#include <functional>

using namespace std;

template <class T>
class Storage {

public: 

	Storage(char* fileName) : filename(fileName) {};

	T saveData(T& data, function<std::string(T)> toStr);
	vector<string> readData();
	T* findOneBy(std::string attr, std::string value, function<T*(string)> strToElem);

private:
	int getLineCount();

	char * filename;
	fstream file;
};