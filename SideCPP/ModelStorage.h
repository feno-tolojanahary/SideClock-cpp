#pragma once
#include <iostream>
#include <vector>
#include "Helper.h"

using namespace std;

class ModelStorage
{
public:
	virtual void setId(int id) = 0;
	virtual int getId() const = 0;
	virtual string getStrHeader() const = 0;
	virtual string stringify(bool convertDate = false) const = 0;
	virtual void populateStr(const vector<string>& headers, const vector<string>& timeclockValues) = 0;
};