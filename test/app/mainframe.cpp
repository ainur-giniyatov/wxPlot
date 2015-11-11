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
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menu_File = new wxMenu();
	wxMenuItem* m_menuItem_Exit;
	m_menuItem_Exit = new wxMenuItem( m_menu_File, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_File->Append( m_menuItem_Exit );
	
	m_menubar1->Append( m_menu_File, wxT("File") ); 
	
	m_menu_options = new wxMenu();
	m_menu1 = new wxMenu();
	wxMenuItem* m_menu1Item = new wxMenuItem( m_menu_options, wxID_ANY, wxT("Scale metrics"), wxEmptyString, wxITEM_NORMAL, m_menu1 );
	wxMenuItem* m_menuItem_time;
	m_menuItem_time = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Time") ) , wxEmptyString, wxITEM_RADIO );
	m_menu1->Append( m_menuItem_time );
	
	wxMenuItem* m_menuItem_secs;
	m_menuItem_secs = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Seconds") ) , wxEmptyString, wxITEM_RADIO );
	m_menu1->Append( m_menuItem_secs );
	
	wxMenuItem* m_menuItem_null;
	m_menuItem_null = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("None") ) , wxEmptyString, wxITEM_RADIO );
	m_menu1->Append( m_menuItem_null );
	
	m_menu_options->Append( m_menu1Item );
	
	m_menubar1->Append( m_menu_options, wxT("Options") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar1->Realize(); 
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel4 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel1 = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_button_newplot = new wxButton( m_panel1, wxID_ANY, wxT("New plot"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_newplot, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_choice_plotsChoices;
	m_choice_plots = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_plotsChoices, 0 );
	m_choice_plots->SetSelection( 0 );
	bSizer2->Add( m_choice_plots, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_choice_seriesChoices;
	m_choice_series = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_seriesChoices, 0 );
	m_choice_series->SetSelection( 0 );
	bSizer2->Add( m_choice_series, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_choice_dataChoices;
	m_choice_data = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_dataChoices, 0 );
	m_choice_data->SetSelection( 0 );
	bSizer2->Add( m_choice_data, 0, wxALL|wxEXPAND, 5 );
	
	m_button1 = new wxButton( m_panel1, wxID_ANY, wxT("Create int"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button1, 0, wxALL|wxEXPAND, 5 );
	
	m_button2 = new wxButton( m_panel1, wxID_ANY, wxT("Create float"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button2, 0, wxALL|wxEXPAND, 5 );
	
	m_button3 = new wxButton( m_panel1, wxID_ANY, wxT("Create 1D float"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button3, 0, wxALL|wxEXPAND, 5 );
	
	m_checkBox_connecttoscale = new wxCheckBox( m_panel1, wxID_ANY, wxT("Connect to scale"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox_connecttoscale->SetValue(true); 
	bSizer2->Add( m_checkBox_connecttoscale, 0, wxALL|wxEXPAND, 5 );
	
	m_button_Fit = new wxButton( m_panel1, wxID_ANY, wxT("Fit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_Fit, 0, wxALL|wxEXPAND, 5 );
	
	m_button_Rename = new wxButton( m_panel1, wxID_ANY, wxT("Rename"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_Rename, 0, wxALL|wxEXPAND, 5 );
	
	m_button_Delete = new wxButton( m_panel1, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_Delete, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer4->Add( m_panel1, 0, wxEXPAND | wxALL, 5 );
	
	m_panel2 = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	
	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
	bSizer4->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel4->SetSizer( bSizer4 );
	m_panel4->Layout();
	bSizer4->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, wxT("1st"), false );
	m_panel8 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel8, wxT("2nd"), false );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItem_Exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_ExitOnMenuSelection ) );
	this->Connect( m_menuItem_time->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_timeOnMenuSelection ) );
	this->Connect( m_menuItem_secs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_secsOnMenuSelection ) );
	this->Connect( m_menuItem_null->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_nullOnMenuSelection ) );
	m_button_newplot->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_newplotOnButtonClick ), NULL, this );
	m_choice_plots->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::m_choice_plotsOnChoice ), NULL, this );
	m_choice_series->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::m_choice_seriesOnChoice ), NULL, this );
	m_choice_data->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::m_choice_dataOnChoice ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button1OnButtonClick ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button2OnButtonClick ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button3OnButtonClick ), NULL, this );
	m_checkBox_connecttoscale->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::m_checkBox_connecttoscaleOnCheckBox ), NULL, this );
	m_button_Fit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_FitOnButtonClick ), NULL, this );
	m_button_Rename->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_RenameOnButtonClick ), NULL, this );
	m_button_Delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_DeleteOnButtonClick ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_ExitOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_timeOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_secsOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_nullOnMenuSelection ) );
	m_button_newplot->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_newplotOnButtonClick ), NULL, this );
	m_choice_plots->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::m_choice_plotsOnChoice ), NULL, this );
	m_choice_series->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::m_choice_seriesOnChoice ), NULL, this );
	m_choice_data->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::m_choice_dataOnChoice ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button1OnButtonClick ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button2OnButtonClick ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button3OnButtonClick ), NULL, this );
	m_checkBox_connecttoscale->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::m_checkBox_connecttoscaleOnCheckBox ), NULL, this );
	m_button_Fit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_FitOnButtonClick ), NULL, this );
	m_button_Rename->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_RenameOnButtonClick ), NULL, this );
	m_button_Delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_DeleteOnButtonClick ), NULL, this );
	
}
