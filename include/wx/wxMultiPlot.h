#pragma once
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/aui.h>

#include "plot_defs.h"
#include "Series.h"
#include "wxSubPlot.h"
#include "wxScaleWidget.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB wxScaleWidget;

	wxDEFINE_EVENT(wxCommandEventQueued, wxCommandEvent);

	class DLLIMPEXP_PLOTLIB wxMultiPlot :
		public wxPanel
	{
	public:
		wxMultiPlot(wxWindow *parent, int orientation = wxVERTICAL);
		virtual ~wxMultiPlot();

		wxSubplot *CreateSubplot(int indx = 0);
		void DeleteSubplot(wxSubplot *subplot);
		const std::vector<wxSubplot *> GetSubplots() { return getsubplots(); };
		void SetLeftWidgetForSubplot(wxSubplot *subplot, wxScaleWidget *scalewidget);
		wxScaleWidget *GetLeftWidgetForSubplot(wxSubplot *subplot);

		wxScaleWidget* GetScaleWidget() { return m_scalewidget; }

		void SetLeftButtonAction(LEFTBUTTON_ACTION lba);
		LEFTBUTTON_ACTION GetLeftButtonAction() { return m_lbaction; }

		void UndoView();
		void RedoView();

		void Fit(int axis_mask);
	private:

		wxFlexGridSizer *m_panelsizer;
		wxScaleWidget *m_scalewidget;

		void OnPlotMenuItem_close(wxCommandEvent &event);
		static const int ID_PLOTMENUITEM_CLOSE;

		void on_plot_view_changed(wxCommandEvent &event);
		void plotviewchanged(int vcd, bool swtc);
		int m_view_change_index;
		int m_orientation;
		//void addplotpane(PlotPane *plotpane);
		void addsubplot(wxSubplot *subplot, int indx);
		LEFTBUTTON_ACTION m_lbaction;

		void OnResize(wxSizeEvent &event);

		//some helpers
		void close_plot_delayed(wxSubplot *subplot);

		const std::vector<wxSubplot *> getsubplots();
		
		void OnMotion(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
		void OnLeftDown(wxMouseEvent &event);
		void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);
		wxBitmap *m_backstore;
		bool m_dragging_resize_resize_border;
		wxRect m_drag_boundary;
		wxWindow *m_above, *m_below;
		void recalc_row_proportions();

		void OnMouseEnter(wxMouseEvent &event);
		void OnMouseLeave(wxMouseEvent &event);
		DECLARE_EVENT_TABLE()


	};

}