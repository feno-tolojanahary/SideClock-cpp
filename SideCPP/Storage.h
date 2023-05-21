#include <fstream>
#include <vector>
#include <optional>
#include <functional>

using namespace std;

template <class T, class TOpt = T>
class Storage {

public: 

	Storage(char* fileName) : filename(fileName) {};

	T saveData(T& data, function<std::string(T)> toStr);
	vector<string> readData();
	std::optional<T> findOneBy(std::string attr, std::string value, function<T(vector<string>, vector<string>)> strToElem);
	bool updateById(const int & id, const TOpt & update, function<string(T)> toStr, function<T(vector<string>, vector<string>)> strToElem);
	vector<T> listData(function<T(vector<string>, vector<string>)> strToElem);

private:
	int getLineCount();

	char * filename;
	fstream file;
};