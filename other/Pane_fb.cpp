///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Pane_fb.h"

///////////////////////////////////////////////////////////////////////////

wxSinglePlot_fb::wxSinglePlot_fb( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	fgSizer3 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer_top = new wxBoxSizer( wxVERTICAL );
	
	
	fgSizer3->Add( bSizer_top, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer_left = new wxBoxSizer( wxHORIZONTAL );
	
	
	fgSizer3->Add( bSizer_left, 1, wxEXPAND, 5 );
	
	m_subplot = new plot::wxSubplot(this);
	fgSizer3->Add( m_subplot, 1, wxEXPAND, 5 );
	
	bSizer_right = new wxBoxSizer( wxHORIZONTAL );
	
	
	fgSizer3->Add( bSizer_right, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer_bottom = new wxBoxSizer( wxVERTICAL );
	
	
	fgSizer3->Add( bSizer_bottom, 1, wxEXPAND, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer3 );
	this->Layout();
}

wxSinglePlot_fb::~wxSinglePlot_fb()
{
}
