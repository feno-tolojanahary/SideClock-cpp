#pragma once
#include <iostream>
#include <vector>
#include "Helper.h"

using namespace std;

class ModelStorage
{
public:
	virtual const string storageName() = 0;
	virtual void setId(int id) = 0;
	virtual int getId() const = 0;
	virtual string getStrDate() const = 0;
	virtual string stringify() const = 0;
	virtual string strOutput() const = 0;
	virtual void populateStr(const vector<string>& headers, const vector<string>& values) = 0;
};