
#include "MyProjectBase.h"

void PingDialog:: m_buttonStartOnButtonClick(wxCommandEvent& event)
{
	// We can set the sizes of individual rows and columns
	// in pixels
	m_grid1->SetRowSize(0, 60);
	m_grid1->SetColSize(0, 120);

	// And set grid cell contents as strings
	m_grid1->SetCellValue(0, 0, "wxGrid is good");

	// We can specify that some cells are read->only
	m_grid1->SetCellValue(0, 3, "This is read->only");
	m_grid1->SetReadOnly(0, 3);

	// Colours can be specified for grid cell contents
	m_grid1->SetCellValue(3, 3, "green on grey");
	m_grid1->SetCellTextColour(3, 3, *wxGREEN);
	m_grid1->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);

	// We can specify the some cells will store numeric
	// values rather than strings. Here we set grid column 5
	// to hold floating point values displayed with width of 6
	// and precision of 2
	m_grid1->SetColFormatFloat(5, 6, 2);
	m_grid1->SetCellValue(0, 6, "3.1415");



}
