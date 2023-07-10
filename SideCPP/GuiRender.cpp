#include "GuiRender.h"


void GuiRender::printListData(vector<vector<string>> contents)
{
	auto table = Table(contents);
	table.SelectAll().Border(LIGHT);
	// Make first row bold with a double border.
	table.SelectRow(0).Decorate(bold);
	table.SelectRow(0).SeparatorVertical(LIGHT);
	table.SelectRow(0).Border(DOUBLE);

	// Align right the "Release date" column.
	table.SelectColumn(2).DecorateCells(align_right);

	// Select row from the second to the last.
	auto content = table.SelectRows(1, -1);
	// Alternate in between 3 colors.
	content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
	content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
	content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

	auto document = table.Render();
	auto screen = Screen::Create(Dimension::Fit(document));
	Render(screen, document);
	screen.Print();
	std::cout << std::endl;
}