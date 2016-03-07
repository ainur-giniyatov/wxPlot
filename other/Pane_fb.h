///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PANE_FB_H__
#define __PANE_FB_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include "wx/wxSubPlot.h"
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class wxSinglePlot_fb
///////////////////////////////////////////////////////////////////////////////
class wxSinglePlot_fb : public wxPanel 
{
	private:
	
	protected:
		wxFlexGridSizer* fgSizer3;
		wxBoxSizer* bSizer_top;
		wxBoxSizer* bSizer_left;
		plot::wxSubplot *m_subplot;
		wxBoxSizer* bSizer_right;
		wxBoxSizer* bSizer_bottom;
	
	public:
		
		wxSinglePlot_fb( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~wxSinglePlot_fb();
	
};

#endif //__PANE_FB_H__
