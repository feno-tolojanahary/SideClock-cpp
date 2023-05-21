#include <fstream>
#include <string>
#include <optional>
#include "Storage.h"
#include "Helper.h"

template <class T, class TOpt>
T Storage<T, TOpt>::saveData(T & data, function<string(T)> toStr) 
{
	data.id = getLineCount();
	std::string dataStr = toStr(data);
	file.open(filename, ios::out | ios::app | ios::binary);
	if (file.is_open()) {
		file << dataStr << std::endl;
		file.close();
	}
	return data;
}

template <class T, class TOpt>
vector<string> Storage<T, TOpt>::readData()
{
	vector<string> content;
	string line;
	file.open(filename, ios::out | ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			content.push_back(line);
		}
	}

	return content;
}

template <class T, class TOpt>
int Storage<T, TOpt>::getLineCount()
{
	int count = 0;
	string line;
	file.open(filename, ios::out | ios::binary);
	if (file.is_open()) {
		while (getline(file, line)) {
			count++;
		}
	}
	file.close();
	return count;
}

template <class T, class TOpt>
std::optional<T> Storage<T, TOpt>::findOneBy(string attr, string value, function<T(vector<string>, vector<string>)> strToElem)
{
	string line;
	int searchAttrIndex = 0;
	vector<string> lineData;

	file.open(filename, ios::out | ios::binary);
	if (file.is_open()) {
		getline(file, line);
		vector<string> header = Helper::splitChar(line);
		for (const string& currentAttr : header) {
			if (currentAttr == attr) break;
			searchAttrIndex++;
		}
		while (getline(file, line)) {
			if (searchAttrIndex < lineData.size()) {
				if (lineData[searchAttrIndex] == value) {
					return strToElem(lineData);
				}
			}
		}
	}
	file.close();
	return {};
}

template <class T, class TOpt>
bool Storage<T, TOpt>::updateById(int id, TOpt update)
{
	
}