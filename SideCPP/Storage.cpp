#include <fstream>
#include <string>
#include <optional>
#include "Storage.h"
#include "Helper.h"
#include "Head.h"

template <class T, class TOpt>
T Storage<T, TOpt>::saveData(T & data, function<string(T)> toStr) 
{
	data.id = getLineCount();
	std::string dataStr = toStr(data);
	file.open(filename, ios::out | ios::app | ios::binary);
	if (!file.is_open())
	{
		return;
	}
	file << dataStr << std::endl;
	file.close();
	return data;
}

template <class T, class TOpt>
vector<string> Storage<T, TOpt>::readData()
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

template <class T, class TOpt>
int Storage<T, TOpt>::getLineCount()
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

template <class T, class TOpt>
std::optional<T> Storage<T, TOpt>::findOneBy(string attr, string value, function<T(vector<string>, vector<string>)> strToElem)
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
				return strToElem(headers, lineData);
			}
		}
	}
	file.close();
	return {};
}

template <class T, class TOpt>
bool Storage<T, TOpt>::updateById(const int & id, const TOpt & update, function<string(T)> toStr, function<T(vector<string>, vector<string>)> strToElem)
{
	string line;
	T foundElem;
	file.open(filename, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		return false;
	}
	long long int pos = file.tellg();
	char* charID = Helper::intToStrFile(id, TYPE_INT_SIZE);
	stringstream sstrIDsearch;
	sstrIDsearch << charID << DELIMITER;
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
				foundElem = strToElem(headers, splitedLine);
				break;
			}
		}
		line.clear();
	}

	if (pos == 0 || foundElem.id != id) return false;
	file.seekp(pos);
	file << toStr(foundElem);
	file.close();
}

template <class T, class TOpt>
vector<T> Storage<T, TOpt>::listData(function<T(vector<string>, vector<string>)> strToElem)
{
	vector<T> data;
	string line;
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
			T elem = strToElem(headers, splitedLine);
			data.push_back(elem);
		}
	}
	file.close();
	return data;
}