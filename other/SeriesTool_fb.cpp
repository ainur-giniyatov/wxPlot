///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SeriesTool_fb.h"

#include "b_fit.png.h"
#include "del_series.png.h"
#include "x_fit.png.h"
#include "y_fit.png.h"

///////////////////////////////////////////////////////////////////////////

SeriesTool_fb::SeriesTool_fb( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_checkBox_name = new wxCheckBox( this, wxID_ANY, wxT("check"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox_name->SetValue(true); 
	m_checkBox_name->SetToolTip( wxT("Show/hide series") );
	
	bSizer1->Add( m_checkBox_name, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );
	
	m_toolBar1 = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_toolBar1->Hide();
	
	m_tool6 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), x_fit_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Horizontal fit"), wxEmptyString, NULL ); 
	
	m_tool7 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), y_fit_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Vertical fit"), wxEmptyString, NULL ); 
	
	m_tool8 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), b_fit_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Fit"), wxEmptyString, NULL ); 
	
	m_tool9 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), del_series_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Delete"), wxEmptyString, NULL ); 
	
	m_toolBar1->Realize(); 
	
	bSizer1->Add( m_toolBar1, 0, 0, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bpButton_fithor = new wxBitmapButton( this, wxID_ANY, x_fit_png_to_wx_bitmap(), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	m_bpButton_fithor->SetToolTip( wxT("Horizontal fit") );
	
	bSizer3->Add( m_bpButton_fithor, 0, 0, 5 );
	
	m_bpButton_fitvert = new wxBitmapButton( this, wxID_ANY, y_fit_png_to_wx_bitmap(), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	m_bpButton_fitvert->SetToolTip( wxT("Vertical fit") );
	
	bSizer3->Add( m_bpButton_fitvert, 0, 0, 5 );
	
	m_bpButton_fit = new wxBitmapButton( this, wxID_ANY, b_fit_png_to_wx_bitmap(), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	m_bpButton_fit->SetToolTip( wxT("Fit") );
	
	bSizer3->Add( m_bpButton_fit, 0, 0, 5 );
	
	m_bpButton_delete = new wxBitmapButton( this, wxID_ANY, del_series_png_to_wx_bitmap(), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	m_bpButton_delete->SetToolTip( wxT("Delete") );
	
	bSizer3->Add( m_bpButton_delete, 0, 0, 5 );
	
	
	bSizer1->Add( bSizer3, 0, wxTOP, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Line") ), wxVERTICAL );
	
	m_checkBox_line_visible = new wxCheckBox( this, wxID_ANY, wxT("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox_line_visible->SetValue(true); 
	sbSizer1->Add( m_checkBox_line_visible, 0, wxBOTTOM, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Style"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	sbSizer1->Add( m_staticText2, 0, wxTOP, 5 );
	
	m_combo_line_style = new wxLineStyleComboBox(this, wxID_ANY);
	sbSizer1->Add( m_combo_line_style, 0, wxBOTTOM|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Weight"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	sbSizer1->Add( m_staticText3, 0, wxTOP, 5 );
	
	m_slider_line_weight = new wxSlider( this, wxID_ANY, 1, 1, 5, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer1->Add( m_slider_line_weight, 0, wxBOTTOM, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	sbSizer1->Add( m_staticText4, 0, wxTOP, 5 );
	
	m_combo_line_colour = new wxColorComboBox(this, wxID_ANY);
	sbSizer1->Add( m_combo_line_colour, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Marks") ), wxVERTICAL );
	
	m_checkBox_marks_visible = new wxCheckBox( this, wxID_ANY, wxT("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox_marks_visible->SetValue(true); 
	sbSizer2->Add( m_checkBox_marks_visible, 0, wxBOTTOM, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Style"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	sbSizer2->Add( m_staticText5, 0, wxTOP, 5 );
	
	m_combo_marks_style = new wxMarkStyleComboBox(this, wxID_ANY);
	sbSizer2->Add( m_combo_marks_style, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	sbSizer2->Add( m_staticText6, 0, wxTOP, 5 );
	
	m_slider_marks_size = new wxSlider( this, wxID_ANY, 2, 1, 10, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer2->Add( m_slider_marks_size, 0, wxBOTTOM, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	sbSizer2->Add( m_staticText7, 0, wxTOP, 5 );
	
	m_combo_marks_colour = new wxColorComboBox(this, wxID_ANY);
	sbSizer2->Add( m_combo_marks_colour, 0, wxEXPAND, 5 );
	
	
	bSizer2->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_checkBox_name->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_checkBox_nameOnCheckBox ), NULL, this );
	m_bpButton_fithor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_fithorOnButtonClick ), NULL, this );
	m_bpButton_fitvert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_fitvertOnButtonClick ), NULL, this );
	m_bpButton_fit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_fitOnButtonClick ), NULL, this );
	m_bpButton_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_deleteOnButtonClick ), NULL, this );
	m_checkBox_line_visible->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_checkBox_line_visibleOnCheckBox ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_checkBox_marks_visible->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_checkBox_marks_visibleOnCheckBox ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
}

SeriesTool_fb::~SeriesTool_fb()
{
	// Disconnect Events
	m_checkBox_name->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_checkBox_nameOnCheckBox ), NULL, this );
	m_bpButton_fithor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_fithorOnButtonClick ), NULL, this );
	m_bpButton_fitvert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_fitvertOnButtonClick ), NULL, this );
	m_bpButton_fit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_fitOnButtonClick ), NULL, this );
	m_bpButton_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_bpButton_deleteOnButtonClick ), NULL, this );
	m_checkBox_line_visible->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_checkBox_line_visibleOnCheckBox ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_slider_line_weight->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SeriesTool_fb::m_slider_line_weightOnScroll ), NULL, this );
	m_checkBox_marks_visible->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SeriesTool_fb::m_checkBox_marks_visibleOnCheckBox ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	m_slider_marks_size->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SeriesTool_fb::m_slider_marks_sizeOnScroll ), NULL, this );
	
}
