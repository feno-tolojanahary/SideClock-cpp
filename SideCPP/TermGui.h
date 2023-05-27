#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include "Helper.h"

#define WRAP_HORIZ_SEP '-'
#define WRAP_VERT_SEP '|'

using namespace std;

template <typename T>
class TermGui {

public:

	TermGui() {};

	vector<vector<string>> castElemForPrint(const vector<T>& elements) const
	{
		vector<vector<string>> castedForPrint;

		for (const T& elem : elements)
		{
			string combinedElemStr = elem.stringify();
			castedForPrint.push_back(Helper::splitChar(combinedElemStr.data(), DELIMITER));
		}
		return castedForPrint;
	}

	string wrapStrResult(const vector<vector<string>>& tableWorld) const
	{
		int rowSize(0);
		const int wordMargin = 3;
		string headFootWrap;
		stringstream ssout;

		if (tableWorld.size() > 1)
		{
			rowSize = static_cast<int>(tableWorld[1].size());
		}
		int *maxColWidths = new int[rowSize]();

		for (const vector<string>& row : tableWorld)
		{
			int colIndex = 0;
			for (const string& word : row)
			{
				if (colIndex <= rowSize)
				{
					int & maxColWidth = *(maxColWidths + colIndex);
					int wrapSize = static_cast<int>(word.size()) + wordMargin;
					if (maxColWidth < wrapSize) maxColWidth = wrapSize;
				}
				colIndex++;
			}
		}

		for (int i = 0; i < rowSize; i++)
		{
			for (int j = 0; j < *(maxColWidths+i); j++)
			{
				headFootWrap += WRAP_HORIZ_SEP;
			}
		}
		headFootWrap += WRAP_HORIZ_SEP;

		delete[] maxColWidths;
		int rowIndex(0);

		for (const vector<string>& row : tableWorld)
		{
			int wordIndex(0);
			rowIndex++;
			ssout << headFootWrap << "\n";
			for (const string& word : row)
			{
				wordIndex++;
				ssout << WRAP_VERT_SEP << " " << word << " ";
				if (static_cast<int>(row.size()) == wordIndex)
				{
					ssout << WRAP_VERT_SEP << "\n";
				}
			}
			if (static_cast<int>(tableWorld.size()) == rowIndex)
			{
				ssout << headFootWrap << "\n";
			}
		}

		return ssout.str();
	}

	void print(const vector<T>& elements) const
	{
		vector<vector<string>> elemReadyToPrint = this->castElemForPrint(elements);
		string printRes = this->wrapStrResult(elemReadyToPrint);

		cout << printRes;
	}
};