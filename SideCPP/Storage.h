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

	Storage(const char* fileName): filename(fileName) {}

	T saveData(T& data)
	{
		streampos begin, end;
		string line;
		int id = generateId();
		data.setId(id);
		fstream file(filename, fstream::out | fstream::app | fstream::binary);
		if (!file.is_open())
		{
			return {};
		}
		string strData = data.stringify();
		
		file.seekg(0, ios::end);
		end = file.tellg();

		if (end == 0)
		{
			string headers = T::getStrHeaderStorage();
			file << headers;
		}
		file << strData;
		file.close();
		return data;
	}
	
	vector<string> readData()
	{
		vector<string> content;
		string line;
		fstream file(filename, fstream::in | fstream::binary);
		if (!file.is_open())
		{
			return content;
		}
		while (getline(file, line)) {
			content.push_back(line);
		}

		return content;
	}

	void findOneBy(string attr, time_t value, T& elem) const
	{
		string line;
		int searchAttrIndex = 0;

		fstream file(filename, fstream::in | fstream::binary);
		if (!file.is_open())
		{
			return;
		}
		getline(file, line);
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		for (const string& currentAttr : headers) {
			if (currentAttr == attr) break;
			searchAttrIndex++;
		}
		while (getline(file, line)) {
			vector<string> lineData = Helper::splitChar(line, DELIMITER);
			if (searchAttrIndex < lineData.size()) {
				if (lineData[searchAttrIndex].c_str() == to_string(value)) {
					elem.populateStr(headers, lineData);
				}
			}
		}
		file.close();
	}

	bool updateById(const int& id, const T& elem) const
	{
		string line;
		T foundElem;
		fstream file(filename, fstream::in | fstream::out | fstream::binary);
		if (!file.is_open())
		{
			return false;
		}
		long long int pos = file.tellg();
		stringstream sstrIDsearch;
		sstrIDsearch << id << DELIMITER;
		string searchID = sstrIDsearch.str();

		getline(file, line);
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		pos = file.tellg();
		for (line; getline(file, line);)
		{
			if (line.find(searchID) != string::npos) {
				vector<string> splitedLine = Helper::splitChar(line, DELIMITER);
				if (stoi(splitedLine[0]) == id) {
					foundElem.populateStr(headers, splitedLine);
					break;
				}
			}
			pos = file.tellg();
			line.clear();
		}

		if (pos == 0 || foundElem.getId() != id) return false;
		file.seekp(pos);
		string dataElem = elem.stringify();
		file << dataElem;
		file.close();
		return true;
	}

	vector<T> listData() const
	{
		vector<T> data;
		string line;
		fstream file(filename, fstream::in | fstream::binary);
		if (!file.is_open())
		{
			return data;
		}
		getline(file, line);
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		while (getline(file, line))
		{
			
		}
		file.close();
		return data;
	}

	vector<T> findDateBetween(const string& attr, const time_t startDate, const time_t endDate) const
	{
		vector<T> foundData;
		string line;
		int searchAttrIndex(0);
		fstream file(filename, fstream::in | fstream::binary);
		if (!file.is_open())
		{
			return foundData;
		}

		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		for (const string& currentAttr : headers) {
			if (currentAttr == attr) break;
			searchAttrIndex++;
		}
		while (getline(file, line))
		{
			if (line.size() > 0) {

				vector<string> lineData = Helper::splitChar(line, DELIMITER);
				if (searchAttrIndex < lineData.size()) {
					string strTimeTcurrent = lineData[searchAttrIndex].c_str();
					if (stoi(strTimeTcurrent) >= startDate && stoi(strTimeTcurrent) <= endDate) {
						T elem;
						elem.populateStr(headers, lineData);
						foundData.push_back(elem);
					}
				}
			}
		}
		file.close();
		return foundData;
	}

	bool deleteById(const int id)
	{
		long long int pos;
		string line{};
		line.reserve(500);
		fstream file(filename, fstream::in | fstream::out | fstream::binary);
		if (!file.is_open())
		{
			return;
		}
		for (line; getline(file, line);)
		{
			vector<string> lineChunks = Helper::splitChar(line, DELIMITER);
			if (strcmp(Helper::trim(lineChunks[0]), to_string(id))
			{
				pos = file.tellg();
				break;
			}
			line.clear();
		}
		if (file.eof()) 
		{
			return false;
		}

		file.seekp(pos);
		file << setfill(' ') << setw(line.size());
		file.close();
		return true;
	}

private:
	int getLineCount()
	{
		int count = 0;
		string line;
		fstream file(filename, fstream::out | fstream::binary);
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

	int generateId()
	{
		int generatedId;
		ifstream file(filename, fstream::in | fstream::binary);
		string strLastTimeclock = getLastLine(file);
		T * tempElem = new T();
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		vector<string> splitedLine = Helper::splitChar(strLastTimeclock, DELIMITER);
		tempElem->populateStr(headers, splitedLine);
		generatedId = tempElem->getId() != -1 ? tempElem->getId() + 1 : 0;
		delete tempElem;
		return generatedId;
	}

	const char * filename;
};

extern template Storage<TimeClock>;