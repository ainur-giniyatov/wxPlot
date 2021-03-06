#pragma once
#include "mainframe.h"
#include "wx/wxSinglePlot.h"
#include "wx/wxMultiPlot.h"
#include "../../other/PopupSeriesTool.h"

class MyFrame :
	public MainFrame
{
public:
	MyFrame();
	virtual ~MyFrame();

private:
	virtual void m_menuItem_ExitOnMenuSelection(wxCommandEvent& event) override;
	virtual void m_button1OnButtonClick(wxCommandEvent& event) override;
	virtual void m_button2OnButtonClick(wxCommandEvent& event) override;
	virtual void m_button3OnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_newplotOnButtonClick(wxCommandEvent& event) override;
	virtual void m_choice_plotsOnChoice(wxCommandEvent& event) override;
	virtual void m_menuItem_timeOnMenuSelection(wxCommandEvent& event) override;
	virtual void m_menuItem_secsOnMenuSelection(wxCommandEvent& event) override;
	virtual void m_menuItem_nullOnMenuSelection(wxCommandEvent& event) override;
	virtual void m_checkBox_connecttoscaleOnCheckBox(wxCommandEvent& event) override;
	virtual void m_choice_seriesOnChoice(wxCommandEvent& event) override;
	virtual void m_choice_dataOnChoice(wxCommandEvent& event) override;
	virtual void m_button_FitOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_RenameOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_DeleteOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_dataupdatedOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_seriesupdateOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_spaceupdateOnButtonClick(wxCommandEvent& event) override;
	virtual void m_menuItem_panOnMenuSelection(wxCommandEvent& event) override;
	virtual void m_menuItem_zoomOnMenuSelection(wxCommandEvent& event) override;
	virtual void m_button_add_boxOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_chartfitxOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_chartfityOnButtonClick(wxCommandEvent& event) override;
	virtual void m_button_chartfitbothOnButtonClick(wxCommandEvent& event) override;
	virtual void m_tool_undo_viewOnToolClicked(wxCommandEvent& event) override;
	virtual void m_tool_redo_viewOnToolClicked(wxCommandEvent& event) override;
	virtual void m_tool_orientOnToolClicked(wxCommandEvent& event) override;

	void OnMouseWheel(wxMouseEvent &event);
	
	void OnMenu_AddLegend(wxCommandEvent &event);
	static const int ID_MENUPLOT_ADDLEGEND;

	void OnMenu_AddVerticalScale(wxCommandEvent &event);
	static const int ID_MENUPLOT_ADDVERTICALSCALE;

	void OnPlotClicked(plot::PlotClickEvent &event);

	plot::wxSinglePlot *m_singleplot;
	plot::Series *m_series;
	plot::wxSubplot *m_subplot;

	plot::wxMultiPlot *m_multiplot;
	plot::Series *m_2ndpageseries;

	
	wxPopupSeriesTool *m_popup_tool;

	//help functions
	void fill_plot_choices();
	void fill_series_choices();

	DECLARE_EVENT_TABLE()
};

