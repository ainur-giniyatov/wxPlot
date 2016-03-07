///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
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
	
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem_pan;
	m_menuItem_pan = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Pan") ) , wxEmptyString, wxITEM_RADIO );
	m_menu3->Append( m_menuItem_pan );
	
	wxMenuItem* m_menuItem_zoom;
	m_menuItem_zoom = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Zoom") ) , wxEmptyString, wxITEM_RADIO );
	m_menu3->Append( m_menuItem_zoom );
	
	m_menubar1->Append( m_menu3, wxT("Action") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY ); 
	m_tool_undo_view = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_GO_BACK, wxART_MENU ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool_redo_view = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_GO_FORWARD, wxART_MENU ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	m_tool_orient = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_REPORT_VIEW, wxART_MENU ), wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxEmptyString, NULL ); 
	
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
	m_button_newplot->SetToolTip( wxT("Add plot") );
	
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
	
	m_button_chartfitx = new wxButton( m_panel1, wxID_ANY, wxT("Chart fit x"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_chartfitx, 0, wxALL|wxEXPAND, 5 );
	
	m_button_chartfity = new wxButton( m_panel1, wxID_ANY, wxT("Chart fit y"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_chartfity, 0, wxALL|wxEXPAND, 5 );
	
	m_button_chartfitboth = new wxButton( m_panel1, wxID_ANY, wxT("Chart fit both"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button_chartfitboth, 0, wxALL|wxEXPAND, 5 );
	
	
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
	m_notebook1->AddPage( m_panel4, wxT("1st"), true );
	m_panel_page2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel5 = new wxPanel( m_panel_page2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_button_dataupdated = new wxButton( m_panel5, wxID_ANY, wxT("DataUpdated()"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button_dataupdated, 0, wxALL|wxEXPAND, 5 );
	
	m_button_seriesupdate = new wxButton( m_panel5, wxID_ANY, wxT("SeriesUpdate()"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button_seriesupdate, 0, wxALL|wxEXPAND, 5 );
	
	m_button_spaceupdate = new wxButton( m_panel5, wxID_ANY, wxT("SpaceUpdate()"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button_spaceupdate, 0, wxALL|wxEXPAND, 5 );
	
	m_button_add_box = new wxButton( m_panel5, wxID_ANY, wxT("Add box"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_button_add_box, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel5->SetSizer( bSizer6 );
	m_panel5->Layout();
	bSizer6->Fit( m_panel5 );
	bSizer5->Add( m_panel5, 0, wxEXPAND | wxALL, 5 );
	
	m_panel6 = new wxPanel( m_panel_page2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER|wxTAB_TRAVERSAL );
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	
	m_panel6->SetSizer( bSizer7 );
	m_panel6->Layout();
	bSizer7->Fit( m_panel6 );
	bSizer5->Add( m_panel6, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel_page2->SetSizer( bSizer5 );
	m_panel_page2->Layout();
	bSizer5->Fit( m_panel_page2 );
	m_notebook1->AddPage( m_panel_page2, wxT("2nd"), false );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItem_Exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_ExitOnMenuSelection ) );
	this->Connect( m_menuItem_time->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_timeOnMenuSelection ) );
	this->Connect( m_menuItem_secs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_secsOnMenuSelection ) );
	this->Connect( m_menuItem_null->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_nullOnMenuSelection ) );
	this->Connect( m_menuItem_pan->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_panOnMenuSelection ) );
	this->Connect( m_menuItem_zoom->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_zoomOnMenuSelection ) );
	this->Connect( m_tool_undo_view->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::m_tool_undo_viewOnToolClicked ) );
	this->Connect( m_tool_redo_view->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::m_tool_redo_viewOnToolClicked ) );
	this->Connect( m_tool_orient->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::m_tool_orientOnToolClicked ) );
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
	m_button_chartfitx->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_chartfitxOnButtonClick ), NULL, this );
	m_button_chartfity->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_chartfityOnButtonClick ), NULL, this );
	m_button_chartfitboth->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_chartfitbothOnButtonClick ), NULL, this );
	m_button_dataupdated->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_dataupdatedOnButtonClick ), NULL, this );
	m_button_seriesupdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_seriesupdateOnButtonClick ), NULL, this );
	m_button_spaceupdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_spaceupdateOnButtonClick ), NULL, this );
	m_button_add_box->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_add_boxOnButtonClick ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_ExitOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_timeOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_secsOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_nullOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_panOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::m_menuItem_zoomOnMenuSelection ) );
	this->Disconnect( m_tool_undo_view->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::m_tool_undo_viewOnToolClicked ) );
	this->Disconnect( m_tool_redo_view->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::m_tool_redo_viewOnToolClicked ) );
	this->Disconnect( m_tool_orient->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::m_tool_orientOnToolClicked ) );
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
	m_button_chartfitx->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_chartfitxOnButtonClick ), NULL, this );
	m_button_chartfity->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_chartfityOnButtonClick ), NULL, this );
	m_button_chartfitboth->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_chartfitbothOnButtonClick ), NULL, this );
	m_button_dataupdated->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_dataupdatedOnButtonClick ), NULL, this );
	m_button_seriesupdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_seriesupdateOnButtonClick ), NULL, this );
	m_button_spaceupdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_spaceupdateOnButtonClick ), NULL, this );
	m_button_add_box->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button_add_boxOnButtonClick ), NULL, this );
	
}
