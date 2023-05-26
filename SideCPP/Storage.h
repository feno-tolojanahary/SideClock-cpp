#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <functional>
#include "TimeClock.h"
#include "Helper.h"

using namespace std;

template <class T>
class Storage {

public: 

	Storage(const char* fileName) : filename(fileName) {};

	T saveData(T& data)
	{
		data.setId(getLineCount());
		fstream file(filename, ios::out | ios::app | ios::binary);
		if (!file.is_open())
		{
			return {};
		}
		string strData = data.stringify();
		file << strData << std::endl;
		file.close();
		return data;
	}
	
	vector<string> readData()
	{
		vector<string> content;
		string line;
		fstream file(filename, ios::out | ios::in);
		if (!file.is_open())
		{
			return content;
		}
		while (getline(file, line)) {
			content.push_back(line);
		}

		return content;
	}

	void findOneBy(string attr, string value, function<void(vector<string>&, vector<string>&, T&)> strToElem, T& elem) const
	{
		string line;
		int searchAttrIndex = 0;

		fstream file(filename, ios::out | ios::binary);
		if (!file.is_open())
		{
			return;
		}
		getline(file, line);
		vector<string> headers = Helper::splitChar(line.data(), DELIMITER);
		for (const string& currentAttr : headers) {
			if (currentAttr == attr) break;
			searchAttrIndex++;
		}
		while (getline(file, line)) {
			vector<string> lineData = Helper::splitChar(line.data(), DELIMITER);
			if (searchAttrIndex < lineData.size()) {
				if (lineData[searchAttrIndex] == value) {
					strToElem(headers, lineData, elem);
				}
			}
		}
		file.close();
	}

	bool updateById(const int& id, function<void(vector<string>&, vector<string>&, T&)> strToElem, const T& elem) const
	{
		string line;
		T foundElem;
		fstream file(filename, ios::in | ios::out | ios::binary);
		if (!file.is_open())
		{
			return false;
		}
		long long int pos = file.tellg();
		stringstream sstrIDsearch;
		sstrIDsearch << id << DELIMITER;
		string searchID = sstrIDsearch.str();

		getline(file, line);
		vector<string> headers = Helper::splitChar(line.data(), DELIMITER);
		pos = file.tellg();

		for (line; getline(file, line);)
		{
			pos = file.tellg();
			if (line.find(searchID) != string::npos) {
				vector<string> splitedLine = Helper::splitChar(line.data(), DELIMITER);
				if (stoi(splitedLine[0]) == id) {
					strToElem(headers, splitedLine, foundElem);
					break;
				}
			}
			line.clear();
		}

		if (pos == 0 || foundElem.getId() != id) return false;
		file.seekp(pos);
		string dataElem = elem.stringify();
		file << dataElem;
		file.close();
		return true;
	}

	vector<T> listData(function<void(vector<string>&, vector<string>&, T&)> strToElem) const
	{
		vector<T> data;
		string line;
		T elem;
		fstream file(filename, ios::out | ios::binary);
		if (!file.is_open())
		{
			return data;
		}
		getline(file, line);
		vector<string> headers = Helper::splitChar(line.data(), DELIMITER);
		while (getline(file, line))
		{
			if (line.size() > 0) {
				vector<string> splitedLine = Helper::splitChar(line.data(), DELIMITER);
				strToElem(headers, splitedLine, elem);
				data.push_back(elem);
			}
		}
		file.close();
		return data;
	}

	int generateId()
	{

	}

private:
	int getLineCount()
	{
		int count = 0;
		string line;
		fstream file(filename, ios::out | ios::binary);
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

	istream& ignoreline(ifstream& in, ifstream::pos_type& pos)
	{
		pos = in.tellg();
		return in.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string getLastLine(std::ifstream& in)
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

	const char * filename;
};

extern template Storage<TimeClock>;