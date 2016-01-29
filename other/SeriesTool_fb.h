///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SERIESTOOL_FB_H__
#define __SERIESTOOL_FB_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include "wxLineStyleComboBox.h"
#include <wx/slider.h>
#include "wxColorComboBox.h"
#include <wx/statbox.h>
#include "wxMarkStyleComboBox.h"
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SeriesTool_fb
///////////////////////////////////////////////////////////////////////////////
class SeriesTool_fb : public wxPanel 
{
	private:
	
	protected:
		wxTreeCtrl* m_treeCtrl1;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_tool6; 
		wxToolBarToolBase* m_tool7; 
		wxToolBarToolBase* m_tool8; 
		wxToolBarToolBase* m_tool9; 
		wxBitmapButton* m_bpButton_fithor;
		wxBitmapButton* m_bpButton_fitvert;
		wxBitmapButton* m_bpButton_fit;
		wxBitmapButton* m_bpButton_delete;
		wxCheckBox* m_checkBox_line_visible;
		wxStaticText* m_staticText2;
		wxLineStyleComboBox *m_combo_line_style;
		wxStaticText* m_staticText3;
		wxSlider* m_slider_line_weight;
		wxStaticText* m_staticText4;
		wxColorComboBox *m_combo_line_colour;
		wxCheckBox* m_checkBox_marks_visible;
		wxStaticText* m_staticText5;
		wxMarkStyleComboBox *m_combo_marks_style;
		wxStaticText* m_staticText6;
		wxSlider* m_slider_marks_size;
		wxStaticText* m_staticText7;
		wxColorComboBox *m_combo_marks_colour;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_checkBox_nameOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_bpButton_fithorOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_bpButton_fitvertOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_bpButton_fitOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_bpButton_deleteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBox_line_visibleOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_slider_line_weightOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_checkBox_marks_visibleOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_slider_marks_sizeOnScroll( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		wxCheckBox* m_checkBox_name;
		
		SeriesTool_fb( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~SeriesTool_fb();
	
};

#endif //__SERIESTOOL_FB_H__
