#include <iostream>
#include <vector>
#include "Helper.h"

#define DELIMITER ","

using namespace std;

class ModelStorage
{
public:
	virtual void setId(int id) = 0;
	virtual string getStrHeader() = 0;
	virtual string stringify() = 0;
};