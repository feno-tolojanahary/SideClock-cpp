#include <fstream>
#include <string>
#include "Storage.h"
#include "Helper.h"

template <class T>
T Storage<T>::saveData(T & data, function<string(T)> toStr) 
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

template <class T>
vector<string> Storage<T>::readData() 
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

template <class T>
int Storage<T>::getLineCount() 
{
	int count = 0;
	string line;
	file.open(filename, ios::out | ios::binary);
	if (file.is_open()) {
		while (getline(file, line)) {
			count++;
		}
	}
	return count;
}

template <class T>
T* Storage<T>::findOneBy(string attr, string value, function<T*(string)> strToElem)
{
	T* foundElem = nullptr;
	string line;
	int lineNumber = 0;
	int searchAttrIndex = 0;
	vector<string> header;
	vector<string> lineData;

	file.open(filename, ios::out | ios::binary);
	if (file.is_open()) {
		while (getline(file, line)) {
			if (lineNumber == 0) {
				header = Helper::splitChar(line);
				for (const string& currentAttr : header) {
					if (currentAttr == attr) break;
					searchAttrIndex++;
				}
			}
			else {
				lineData = Helper::splitChar(line);
				if (searchAttrIndex < lineData.size()) {
					if (lineData[searchAttrIndex] == value) {
						foundElem = strToElem(lineData);
					}
				}
			}
			
			lineNumber++;
		}
	}
	return foundElem;
}

