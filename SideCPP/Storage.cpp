#include <fstream>
#include <string>
#include <optional>
#include "Storage.h"
#include "Helper.h"
#include "Head.h"

template <class T>
T Storage<T>::saveData(T & data) 
{
	data.setId(getLineCount());
	file.open(filename, ios::out | ios::app | ios::binary);
	if (!file.is_open())
	{
		return;
	}
	file << data.stringify( << std::endl;
	file.close();
	return data;
}

template <class T>
vector<string> Storage<T>::readData()
{
	vector<string> content;
	string line;
	file.open(filename, ios::out | ios::in);
	if (!file.is_open())
	{
		return content;
	}
	while (getline(file, line)) {
		content.push_back(line);
	}

	return content;
}

template <class T>
int Storage<T>::getLineCount()
{
	int count = 0;
	string line;
	file.open(filename, ios::out | ios::binary);
	if (!file.is_open())
	{
		return 0;
	}
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;
}

template <class T>
void Storage<T>::findOneBy(string attr, string value, function<T&(vector<string>&, vector<string>&, T&)> strToElem, T& elem) const
{
	string line;
	int searchAttrIndex = 0;

	file.open(filename, ios::out | ios::binary);
	if (!file.is_open())
	{
		return {};
	}
	getline(file, line);
	vector<string> headers = Helper::splitChar(line);
	for (const string& currentAttr : headers) {
		if (currentAttr == attr) break;
		searchAttrIndex++;
	}
	while (getline(file, line)) {
		vector<string> lineData = Helper::splitChar(line);
		if (searchAttrIndex < lineData.size()) {
			if (lineData[searchAttrIndex] == value) {
				strToElem(headers, lineData, elem);
			}
		}
	}
	file.close();
}

template <class T>
bool Storage<T>::updateById(const int & id, function<T& (vector<string>&, vector<string>&, T&)> strToElem, const T& elem) const
{
	string line;
	T foundElem;
	file.open(filename, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		return false;
	}
	long long int pos = file.tellg();
	stringstream sstrIDsearch;
	sstrIDsearch << id << DELIMITER;
	string searchID = sstrIDsearch.str();

	getline(file, line);
	vector<string> headers = Helper::splitChar(line);
	pos = file.tellg();

	for (line; getline(file, line);)
	{
		pos = file.tellg();
		if (line.find(searchID) != string::npos) {
			vector<string> splitedLine = Helper::splitChar(line);
			if (stoi(splitedLine[0]) == id) {
				strToElem(headers, splitedLine, foundElem);
				break;
			}
		}
		line.clear();
	}

	if (pos == 0 || foundElem.id != id) return false;
	file.seekp(pos);
	file << elem.stringify();
	file.close();
}

template <class T>
vector<T> Storage<T>::listData(function<T& (vector<string>&, vector<string>&, T&)> strToElem) const
{
	vector<T> data;
	string line;
	T elem;
	file.open(filename, ios::out | ios::binary);
	if (!file.is_open())
	{
		return false;
	}
	getline(file, line);
	vector<string> headers = Helper::splitChar(line);
	while (getline(file, line)) 
	{
		if (line.size() > 0) {
			vector<string> splitedLine = Helper::splitChar(line);
			strToElem(headers, splitedLine, elem);
			data.push_back(elem);
		}
	}
	file.close();
	return data;
}

template <class T>
istream& Storage<T>::ignoreline(ifstream& in, ifstream::pos_type& pos)
{
	pos = in.tellg();
	return in.ignore(numeric_limits<streamsize>::max(), '\n');
}

template <class T>
string Storage<T>::getLastLine(ifstream& in)
{
	ifstream::pos_type pos = in.tellg();

	ifstream::pos_type lastPos;
	while (in >> std::ws && ignoreline(in, lastPos))
		pos = lastPos;

	in.clear();
	in.seekg(pos);

	string line;
	getline(in, line);
	return line;
}

template <class T>
int Storage<T>::generateId()
{

}


