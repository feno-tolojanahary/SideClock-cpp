#include <fstream>
#include <vector>
#include <optional>
#include <functional>

using namespace std;

template <class T>
class Storage {

public: 

	Storage(char* fileName) : filename(fileName) {};

	T saveData(T& data);
	vector<string> readData();
	void findOneBy(std::string attr, std::string value, function<T& (vector<string>&, vector<string>&, T&)> strToElem, T& elem) const;
	bool updateById(const int& id, function<T& (vector<string>&, vector<string>&, T&)> strToElem, const T& elem) const;
	vector<T> listData(function<T& (vector<string>&, vector<string>&, T&)> strToElem) const;
	int generateId();

private:
	int getLineCount();
	istream& ignoreline(ifstream& in, ifstream::pos_type& pos);
	string getLastLine(std::ifstream& in);

	char * filename;
	fstream file;
};