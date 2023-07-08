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
		int searchAttrIndex(0);
		bool foundAttrIndex(false);

		fstream file(filename, fstream::in | fstream::binary);
		if (!file.is_open())
		{
			return;
		}
		getline(file, line);
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		for (const string& currentAttr : headers) {
			if (currentAttr == attr) {
				foundAttrIndex = true;
				break;
			}
			searchAttrIndex++;
		}
		if (!foundAttrIndex) return;
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
		vector<T> foundData;
		string line;
		fstream file(filename, fstream::in | fstream::binary);
		if (!file.is_open())
		{
			return foundData;
		}
		getline(file, line);
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		while (getline(file, line))
		{
			if (line.size() > 0) {
				T elem;
				vector<string> lineData = Helper::splitChar(line, DELIMITER);
				elem.populateStr(headers, lineData);
				foundData.push_back(elem);
			}
		}
		file.close();
		return foundData;
	}

	vector<T> findDateBetween(const string& attr, const time_t& startDate, const time_t& endDate) const
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

	bool deleteById(const int& id)
	{
		int lineIndex = 0, lineIndexRemoval = 0;
		string line{};
		const string tempFilename = "tempfile";
		bool isDeleted = false;
		line.reserve(500);

		fstream file(filename, fstream::in | fstream::out | fstream::binary);
		fstream tempFile(tempFilename, fstream::out | fstream::binary);

		if (!file.is_open() || !tempFile.is_open())
		{
			cout << "Error when deleting element." << endl;
			return false;
		}
		int lineIndexRemoval = Storage<T>::lineIndexById(file, id);
		file.seekg(0);
		for (line; getline(file, line);)
		{
			lineIndex++;
			if (lineIndex == lineIndexRemoval) {
				tempFile << line << endl;
				isDeleted = true;
				break;
			} 
		}
		remove(filename);
		rename(tempFilename, filename);
		return isDeleted;
	}

	int deleteByDate(const string& attrName, const string& date)
	{
		string line{}, headerLine{};
		int attrIndex(0), deletedCount(0);
		bool foundAttrIndex(false);
		const string tempFilename = "tempfile";
		fstream file(filename, fstream::in | fstream::binary);
		fstream tempFile(tempFilename, fstream::out | fstream::binary);

		if (!file.is_open() || !tempFile.is_open())
		{
			cout << "Error when deleting element." << endl;
			return 0;
		}
		getline(file, headerLine);
		tempFile << headerLine;
		for (const string headerName : Helper::splitChar(headerLine, DELIMITER)) {
			if (strcmp(attrName, headerName) == 0) {
				foundAttrIndex = true;
				break;
			}
			attrIndex++;
		}
		if (!foundAttrIndex) return 0;
		for (line; getline(file, line))
		{
			struct tm tmLineDate;
			char buffFormatedLineDate[10];
			vector<string> splitedLine = Helper::splitChar(line, DELIMITER);
			time_t dateVal = stod(splitedLine[attrIndex]);
			gmtime_s(&tmLineDate, &dateVal);
			strftime(buffFormatedLineDate, sizeof buffFormatedLineDate, FORMAT_DATE, &tmLineDate);
			if (strcmp(date, buffFormatedLineDate) == 0) {
				deletedCount++;
			}
			else {
				tempFile << line;
			}
		}
		remove(filename);
		rename(tempFilename, filename);
		return deletedCount;
	}

	int deleteBetweenADate(const string& attrName, const string& strStartDate, const string& strEndDate)
	{
		string line{}, headerLine{};
		bool foundAttrIndex(false);
		int attrIndex(0), deletedCount(0);
		const string tempFilename = "tempfile";
		fstream file(filename, fstream::in | fstream::binary);
		fstream tempFile(tempFilename, fstream::out | fstream::binary);

		if (!file.is_open() || !tempFile.is_open())
		{
			cout << "Error when deleting element." << endl;
			return 0;
		}
		for (const string headerName : Helper::splitChar(headerLine, DELIMITER)) {
			if (strcmp(startAttrName, headerName) == 0) {
				foundAttrIndex = true;
				break;
			}
			attrIndex++;
		}
		if (!foundAttrIndex) return 0;
		time_t startDate = Helper::stringToTime(strStartDate, FORMAT_DATE);
		time_t endDate = Helper::stringToTime(strEndDate, FORMAT_DATE);
		for (line; getline(file, line))
		{
			if (line.size() == 0) break;
			time_t lineDate = stod(Helper::splitChar(headerLine, DELIMITER));
			if (lineDate >= startDate && lineDate <= endDate) {
				deletedCount++;
				break;
			}
			tempFile << line;
		}
		remove(filename);
		rename(tempFilename, filename);
		return deletedCount;
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

	static int lineIndexById(fstream& targetFile, const int& id)
	{
		int lineIndex(0);
		string line;
		stringstream sstrIDsearch;
		sstrIDsearch << id << DELIMITER;
		string searchID = sstrIDsearch.str();

		if (!targetFile.is_open()) {
			return 0;
		}
		while (getline(file, line)) {
			lineIndex++;
			if (line.find(searchID) != string::npos) {
				vector<string> splitedLine = Helper::splitChar(line, DELIMITER);
				if (stoi(splitedLine[0]) == id)
					break;
			}
		}
		return lineIndex;
	}

	static int lineIndexByAttr(fstream& targetFile, const string& attrName, const auto& value)
	{
		string line;
		int attrIndex(0), lineIndex(0);
		if (!targetFile.is_open()) {
			return 0;
		}
		vector<string> headers = Helper::splitChar(T::getStrHeaderStorage(), DELIMITER);
		for (const string& currentAttr : headers) {
			if (currentAttr == attrName) break;
			attrIndex++;
		}
		while (getline(targetFile, line)) {
			lineIndex++;
			vector<string> lineData = Helper::splitChar(line, DELIMITER);
			if (attrIndex < lineData.size()) {
				if (lineData[attrIndex].c_str() == to_string(value)) {
					break;
				}
			}
		}
		return lineIndex;
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