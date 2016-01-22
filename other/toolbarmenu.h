///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TOOLBARMENU_H__
#define __TOOLBARMENU_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ToolBarMenu
///////////////////////////////////////////////////////////////////////////////
class ToolBarMenu : public wxToolBar 
{
	private:
	
	protected:
	
	public:
		wxToolBarToolBase* m_tool_fitvert; 
		wxToolBarToolBase* m_tool_fithor; 
		wxToolBarToolBase* m_tool_fitall; 
		wxToolBarToolBase* m_tool_properties; 
		wxToolBarToolBase* m_tool_delete; 
		
		ToolBarMenu( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0 );
		~ToolBarMenu();
	
};

#endif //__TOOLBARMENU_H__
