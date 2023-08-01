#pragma once
#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

class HelperStore {

	static Field fieldByName(const string& fieldName, const vector<Field> columnsInfo) 
	{
		for (vector<Field>::iterator it = columnsInfo.begin(); it != columnsInfo.end(); it++)
		{
			if (it->name == fieldName) {
				return *it;
			}
		}
	}
};