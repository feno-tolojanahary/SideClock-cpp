#include "TermGui.h"

template <class T>
vector<vector<string>> TermGui<T>::castElemForPrint(const vector<T>& elements) const
{
	vector<vector<string>> castedForPrint;

	for (const T& elem : elements)
	{
		string combinedElemStr = elem.stringify();
		castedForPrint.push_back(Helper::splitChar(combinedElemStr, DELIMITER));
	}
	return castedForPrint;
}

template <class T>
string TermGui<T>::wrapStrResult(const vector<vector<string>>& tableWorld) const
{
	int colIndex(0), rowIndex(0), defaultWordColWidth(0);
	int* wordColWidth = &defaultWordColWidth;
	int const wordMargin = 4;
	stringstream ssout;

	for (const vector<string>& row : tableWorld)
	{
		for (const string& word : row)
		{
			int colLength = row.size() + wordMargin;
			if (*wordColWidth < colLength) wordColWidth = &colLength;
		}
	}

	int wrapperWidth = *wordColWidth + wordMargin;
	char* headFootStr = new char[wrapperWidth];
	for (int i = 0; i < wrapperWidth; i++)
	{
		headFootStr[i] = WRAP_HORIZ_SEP;
	}

	int rowIndex(0);
	for (const vector<string>& row : tableWorld)
	{
		int wordIndex(0);
		rowIndex++;
		ssout << headFootStr << endl;
		for (const string& word : row)
		{
			ssout << WRAP_VERT_SEP << " " << word;
			wordIndex++;
			if (wordIndex == row.size())
			{
				ssout << " " << WRAP_VERT_SEP << endl;
			}
		}

		if (rowIndex == tableWorld.size())
		{
			ssout << headFootStr << endl;
		}
	}
}

template <class T>
void TermGui<T>::print(const vector<T>& elements) const
{
	vector<vector<string>> elemReadyToPrint = this->castElemForPrint(elements);
	string printRes = this->wrapStrResult(elemReadyToPrint);

	cout << printRes;
}