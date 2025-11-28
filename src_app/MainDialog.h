#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

#include <wx/timer.h>

#include <map>

#include "MyProjectBase.h"
#include "BG_ICMP.h"




class MainDialog : public PingDialog
{

	//https://learn.microsoft.com/en-us/windows/win32/api/ipexport/ns-ipexport-icmp_echo_reply
	std::map<int, std::string> ICMP_Status{ {0, "IP_SUCCESS"}, {11001, "IP_BUF_TOO_SMALL"}, {11002, "IP_DEST_NET_UNREACHABLE"} ,
	{11003, "IP_DEST_HOST_UNREACHABLE"} , {11004, "IP_DEST_PROT_UNREACHABLE"} , {11005, "IP_DEST_PORT_UNREACHABLE"} , {11006, "IP_NO_RESOURCES"} ,
	{11007, "IP_BAD_OPTION"} ,{11008, "IP_HW_ERROR"} ,{11009, "IP_PACKET_TOO_BIG"} ,{11010, "IP_REQ_TIMED_OUT"} ,{11011, "IP_BAD_REQ"} ,
	{11012, "IP_BAD_ROUTE"} , {11013, "IP_TTL_EXPIRED_TRANSIT"} , {11014, "IP_TTL_EXPIRED_REASSEM"} , {11015, "IP_PARAM_PROBLEM"} , {11016, "IP_SOURCE_QUENCH"} ,
	{11017, "IP_OPTION_TOO_BIG"} , {11018, "IP_BAD_DESTINATION"} , {11018, "IP_GENERAL_FAILURE"} };




	private:

	protected:

		wxTimer m_timer1;


		// Virtual event handlers, override them in your derived class
		void m_buttonStartOnButtonClick( wxCommandEvent& event ) override
		{
			pme("Starting Single Scan");
			ScanIPList();
			ShowScanList();

			auto a = this->GetSize();
			pme("Size: %d %d", a.x, a.y);
			pme("Timer is %srunning", m_timer1.IsRunning() ? "" : "not ");

			/*
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
			//m_grid1->SetCellValue(0, 6, "3.1415");
			*/

		}
		void m_buttonStopOnButtonClick( wxCommandEvent& event ) override
		{

			if (m_timer1.IsRunning())
			{
				m_timer1.Stop();
				m_buttonStop->SetLabel("Start Periodic");
				pme("Stopping Timer");
			}
			else
			{
				bool retVal = m_timer1.Start();
				m_buttonStop->SetLabel("Stop Periodic");
				pme("Starting Timer returned %c", retVal?'T':'F');
			}

			ShowScanList();

			/*

			// Append a new row
			m_grid1->AppendRows(1);

			// Get the index of the newly added row
			int newRowIndex = m_grid1->GetNumberRows() - 1;

			// Set some data in the new row
			m_grid1->SetCellValue(newRowIndex, 0, wxString::Format("New Row %d, Col 0", newRowIndex));
			m_grid1->SetCellValue(newRowIndex, 1, wxString::Format("New Row %d, Col 1", newRowIndex));


			// Optional: Auto-size rows/columns if needed
			m_grid1->AutoSizeRows();
			m_grid1->AutoSizeColumns();

			m_grid1->ForceRefresh(); // Force immediate repaint

			bSizer1->Fit(this); // Size the dialog to fit its content
			*/

		}


		void m_comboBoxSitesOnCombobox(wxCommandEvent& event) override
		{
			BuildScanList();
		}


		void pme(const char* fmt, ...);
		void SetRow(aNetDevice a, int row);

		void BuildScanList(void);
		void ShowScanList();
		void m_timer1OnTimer(wxTimerEvent& event);

		



public:

	MainDialog(wxWindow* parent) : PingDialog(parent) //wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("RCS Ping Tester"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxDIALOG_NO_PARENT | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU)
	{
		//wxMessageBox(_T("Here!"), _T("Info"));
		// Give the frame/app an icon
		SetIcon(wxICON(sample));

		pme("Constructor");

		m_timer1.SetOwner(this, m_timer1.GetId());
		m_timer1.Start(1000);
		this->Connect(m_timer1.GetId(), wxEVT_TIMER, wxTimerEventHandler(MainDialog::m_timer1OnTimer));

		InitICMP();

		m_grid1->SetColLabelValue(0, "State");
		m_grid1->SetColSize(0, 40);

		m_grid1->SetColLabelValue(1, "IP");
		m_grid1->SetColSize(0, 150);

		m_grid1->SetColLabelValue(2, "Host Name");
		m_grid1->SetColSize(0, 180);

		m_grid1->SetColLabelValue(3, "#Ping\r\nTries");
		m_grid1->SetColSize(3, 85);

		m_grid1->SetColLabelValue(4, "#Ping\r\nSuccess");
		m_grid1->SetColSize(4, 85);

		m_grid1->SetColLabelValue(5, "RTT [ms]");
		m_grid1->SetColLabelValue(6, "Last Ping");
		m_grid1->SetColSize(6, 260);

		m_grid1->SetColLabelValue(7, "Notes");
		m_grid1->SetColSize(7, 300);

		m_grid1->SetColFormatNumber(3);
		m_grid1->SetColFormatNumber(4);

		//m_comboBoxSites = new wxComboBox(this, wxID_ANY, _("436Sqn"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
		m_comboBoxSites->Append(_("436Sqn"));
		m_comboBoxSites->Append(_("22 Wing"));
		m_comboBoxSites->Append(_("3 Wing"));
		m_comboBoxSites->Append(_("4 Wing"));
		m_comboBoxSites->Append(_("TSIL"));
		m_comboBoxSites->Append(_("RSIL"));
		m_comboBoxSites->Select(0);


		BuildScanList();

		ScanIPList();
		ShowScanList();

		if (m_timer1.IsRunning())
		{
			m_buttonStop->SetLabel("Stop Periodic");
		}
		else
		{
			m_buttonStop->SetLabel("Start Periodic");
		}


	};


	~MainDialog()
	{
		ShutDownICMP();
	}

};

