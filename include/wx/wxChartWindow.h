#pragma once
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/aui.h>

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "wxPlotWindow.h"
#include "ScaleWindow.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Axis;
	class DLLIMPEXP_PLOTLIB wxPlotWindow;
	class DLLIMPEXP_PLOTLIB ScaleWindow;

	wxDEFINE_EVENT(wxCommandEventQueued, wxCommandEvent);

	class DLLIMPEXP_PLOTLIB wxChartWindow :
		public wxPanel
	{
	public:
		wxChartWindow(wxWindow *parent, int orientation = wxVERTICAL);
		virtual ~wxChartWindow();
		wxPanel *GetPlotContainer() { return m_plotscontainer; }

		wxPlotWindow *CreatewxPlotWindow();
		ScaleWindow* GetScaleWindow() { return m_scale; }
		void DeletePlot(wxPlotWindow *plot);

		void SetLeftButtonAction(LEFTBUTTON_ACTION lba);
		LEFTBUTTON_ACTION GetLeftButtonAction() { return m_lbaction; }

		void UndoView();
		void RedoView();

		void Fit(int axis_mask);
	private:

		wxSizer *m_sizer;
		ScaleWindow *m_scale;
		wxPanel *m_plotscontainer;

		wxAuiManager m_mgr;

		void OnPlotMenuItem_close(wxCommandEvent &event);
		static const int ID_PLOTMENUITEM_CLOSE;

		void on_plot_view_changed(wxCommandEvent &event);
		void plotviewchanged(int vcd, bool swtc);
		int m_view_change_index;
		int m_orientation;
		void addplot(wxPlotWindow *plot);

		LEFTBUTTON_ACTION m_lbaction;

		DECLARE_EVENT_TABLE()

		//some helpers
		void close_plot_delayed(wxPlotWindow *plot);
		std::vector<wxPlotWindow *> getplots();
	};

}