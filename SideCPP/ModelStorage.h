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
	virtual string stringify() const = 0;
	virtual string strOutput() const = 0;
	virtual void populateStr(const vector<string>& headers, const vector<string>& values) = 0;
};