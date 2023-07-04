#pragma once
#include <iostream>
#include "lib/args-parser-master/args-parser/all.hpp"

using namespace std;

class ArgsParsing {

public:
	ArgsParsing(int argc, char* argv[]);
	void init();

private:
	int argc;
	char** argv;
};