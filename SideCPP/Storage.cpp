#include <fstream>
#include <string>
#include <functional>
#include "Storage.h"

template <class T>
T Storage<T>::saveData(T & data, function<std::string(T)> toStr) 
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
T Storage<T>::findByCondition(std::string attr, auto value)
{

}

