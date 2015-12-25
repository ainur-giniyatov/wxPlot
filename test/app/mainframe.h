///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu_File;
		wxMenu* m_menu_options;
		wxMenu* m_menu1;
		wxMenu* m_menu3;
		wxToolBar* m_toolBar1;
		wxStatusBar* m_statusBar1;
		wxNotebook* m_notebook1;
		wxPanel* m_panel4;
		wxPanel* m_panel1;
		wxButton* m_button_newplot;
		wxChoice* m_choice_plots;
		wxChoice* m_choice_series;
		wxChoice* m_choice_data;
		wxButton* m_button1;
		wxButton* m_button2;
		wxButton* m_button3;
		wxCheckBox* m_checkBox_connecttoscale;
		wxButton* m_button_Fit;
		wxButton* m_button_Rename;
		wxButton* m_button_Delete;
		wxPanel* m_panel2;
		wxBoxSizer* bSizer3;
		wxPanel* m_panel_page2;
		wxPanel* m_panel5;
		wxButton* m_button_dataupdated;
		wxButton* m_button_seriesupdate;
		wxButton* m_button_spaceupdate;
		wxButton* m_button_add_box;
		wxPanel* m_panel6;
		wxBoxSizer* bSizer7;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_menuItem_ExitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_menuItem_timeOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_menuItem_secsOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_menuItem_nullOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_menuItem_panOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_menuItem_zoomOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_newplotOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_choice_plotsOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_choice_seriesOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_choice_dataOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button1OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button2OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button3OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBox_connecttoscaleOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_FitOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_RenameOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_DeleteOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_dataupdatedOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_seriesupdateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_spaceupdateOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_add_boxOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MainFrame"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 642,482 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

#endif //__MAINFRAME_H__
