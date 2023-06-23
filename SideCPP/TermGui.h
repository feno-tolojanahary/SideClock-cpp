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

		if (elements.size() > 0) {
			castedForPrint.push_back(Helper::splitChar(elements[1].getStrHeader(), DELIMITER));
		}
		for (const T& elem : elements)
		{
			string combinedElemStr = elem.strOutput();
			castedForPrint.push_back(Helper::splitChar(combinedElemStr.data(), DELIMITER));
		}
		return castedForPrint;
	}

	void wrapStrResult(const vector<vector<string>>& tableWorld, const size_t& rowSize, stringstream &ssout) const
	{
		const int wordMargin = 3;
		string headFootWrap;

		if (rowSize < 1)
		{
			return;
		}

		int *maxColWidths = new int[rowSize]();

		for (int i = 0; i < rowSize; i++)
		{
			*(maxColWidths + i) = 0;
		}

		for (const vector<string>& row : tableWorld)
		{
			int colIndex = 0;
			for (const string& word : row)
			{
				if (colIndex < rowSize)
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
				int space = *(maxColWidths + (wordIndex - 1)) - static_cast<int>(word.size()) - wordMargin ;
				for (int j = 0; j < space; j++)
				{
					ssout << " ";
				}
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

		delete[] maxColWidths;
	}

	void print(const vector<T>& elements) const
	{
		stringstream ssout;
		vector<vector<string>> elemReadyToPrint = this->castElemForPrint(elements);
		int rowSize = 0;
		if (elemReadyToPrint.size > 0)
		{
			rowSize = elemReadyToPrint.size();
		}
		this->wrapStrResult(elemReadyToPrint, rowSize, ssout);

		cout << ssout.str();
	}


};