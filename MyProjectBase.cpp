///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProjectBase.h"

///////////////////////////////////////////////////////////////////////////

PingDialog::PingDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,200 ), wxDefaultSize );

	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );

	m_buttonStart = new wxButton( this, wxID_ANY, _("Run Once"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonStart, 0, wxALL, 5 );

	m_buttonStop = new wxButton( this, wxID_ANY, _("Stop Peridodic"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonStop, 0, wxALL, 5 );

	m_comboBoxSites = new wxComboBox( this, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizerButtons->Add( m_comboBoxSites, 0, wxALL, 5 );


	bSizer1->Add( bSizerButtons, 1, wxFIXED_MINSIZE, 5 );

	wxBoxSizer* bSizerStatus;
	bSizerStatus = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Status") ), wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 3, 0, 0 );

	m_staticText1 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Alive"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gSizer1->Add( m_staticText1, 0, wxALL, 5 );

	m_staticText2 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Dead"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Zombie"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL, 5 );

	m_textCtrlAlive = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textCtrlAlive, 0, wxALL, 5 );

	m_textCtrlDead = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textCtrlDead, 0, wxALL, 5 );

	m_textCtrlZombie = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textCtrlZombie, 0, wxALL, 5 );


	sbSizer4->Add( gSizer1, 1, wxEXPAND, 5 );


	bSizer4->Add( sbSizer4, 1, wxEXPAND, 5 );


	bSizerStatus->Add( bSizer4, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizerStatus, 2, wxFIXED_MINSIZE, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("label") ), wxVERTICAL );

	m_grid1 = new wxGrid( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid1->CreateGrid( 5, 8 );
	m_grid1->EnableEditing( true );
	m_grid1->EnableGridLines( true );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );

	// Columns
	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( true );
	m_grid1->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_grid1->EnableDragRowSize( true );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_grid1->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sbSizer1->Add( m_grid1, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( sbSizer1, 8, wxEXPAND, 5 );

	m_textCtrlDebug = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer1->Add( m_textCtrlDebug, 4, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PingDialog::m_buttonStartOnButtonClick ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PingDialog::m_buttonStopOnButtonClick ), NULL, this );
	m_comboBoxSites->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PingDialog::m_comboBoxSitesOnCombobox ), NULL, this );
}

PingDialog::~PingDialog()
{
}
