#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

#define WRAP_HORIZ_SEP '-'
#define WRAP_VERT_SEP '|'

using namespace std;

template <class T>
class TermGui {

public:

	vector<vector<string>> castElemForPrint(const vector<T>& elements) const;

	string wrapStrResult(const vector<vector<string>>& tableWorld) const;

	void print(const vector<T>& elements) const;
};