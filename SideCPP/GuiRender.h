#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"
#include "ftxui/screen/screen.hpp"

using namespace std;
using namespace ftxui;

class GuiRender {

public:

	void printListData(vector<vector<string>> contents);
};