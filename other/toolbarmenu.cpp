///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "toolbarmenu.h"

#include "b_fit.bmp.h"
#include "colorstyle.bmp.h"
#include "del_series.bmp.h"
#include "x_fit.bmp.h"
#include "y_fit.bmp.h"

///////////////////////////////////////////////////////////////////////////

ToolBarMenu::ToolBarMenu( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxToolBar( parent, id, pos, size, style )
{
	m_tool_fitvert = AddTool( wxID_ANY, wxT("tool"), y_fit_bmp_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Vertical fit this series"), wxEmptyString, NULL ); 
	
	m_tool_fithor = AddTool( wxID_ANY, wxT("tool"), x_fit_bmp_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Horizontal fit this series"), wxEmptyString, NULL ); 
	
	m_tool_fitall = AddTool( wxID_ANY, wxT("tool"), b_fit_bmp_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Fit this series"), wxEmptyString, NULL ); 
	
	m_tool_properties = AddTool( wxID_ANY, wxT("tool"), colorstyle_bmp_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Property dialog for this sereis"), wxEmptyString, NULL ); 
	
	m_tool_delete = AddTool( wxID_ANY, wxT("tool"), del_series_bmp_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Delete this series"), wxEmptyString, NULL ); 
	
	
	Realize();
}

ToolBarMenu::~ToolBarMenu()
{
}
