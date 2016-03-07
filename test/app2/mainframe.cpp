///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "mainframe.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer_left;
	bSizer_left = new wxBoxSizer( wxVERTICAL );
	
	m_button15 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_left->Add( m_button15, 0, wxALL, 5 );
	
	
	bSizer8->Add( bSizer_left, 0, wxEXPAND, 5 );
	
	bSizer_center = new wxBoxSizer( wxVERTICAL );
	
	m_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer_panel = new wxBoxSizer( wxVERTICAL );
	
	
	m_panel->SetSizer( bSizer_panel );
	m_panel->Layout();
	bSizer_panel->Fit( m_panel );
	bSizer_center->Add( m_panel, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer_center, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
	m_menubar2 = new wxMenuBar( 0 );
	m_menu4 = new wxMenu();
	m_menubar2->Append( m_menu4, wxT("File") ); 
	
	this->SetMenuBar( m_menubar2 );
	
	m_statusBar2 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}
