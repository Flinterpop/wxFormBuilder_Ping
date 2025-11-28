///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/grid.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PingDialog
///////////////////////////////////////////////////////////////////////////////
class PingDialog : public wxDialog
{
	private:

	protected:
		wxBoxSizer* bSizer1;
		wxButton* m_buttonStart;
		wxButton* m_buttonStop;
		wxComboBox* m_comboBoxSites;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrlAlive;
		wxTextCtrl* m_textCtrlDead;
		wxTextCtrl* m_textCtrlZombie;
		wxGrid* m_grid1;
		wxTextCtrl* m_textCtrlDebug;

		// Virtual event handlers, override them in your derived class
		virtual void m_buttonStartOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_buttonStopOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_comboBoxSitesOnCombobox( wxCommandEvent& event ) { event.Skip(); }


	public:

		PingDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("RCS Ping Tester"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 503,535 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );

		~PingDialog();

};

