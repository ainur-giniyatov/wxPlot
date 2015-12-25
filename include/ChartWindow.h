#pragma once
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/aui.h>

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Space.h"
#include "PlotWindow.h"
#include "ScaleWindow.h"

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB PlotWindow;
class WXDLLIMPEXP_PLOTLIB ScaleWindow;

wxDEFINE_EVENT(wxCommandEventQueued, wxCommandEvent);

class WXDLLIMPEXP_PLOTLIB ChartWindow :
	public wxPanel
{
public:
	ChartWindow(wxWindow *parent, int orientation = wxVERTICAL);
	virtual ~ChartWindow();
	wxPanel *GetPlotContainer() { return m_plotscontainer; }

	PlotWindow *CreatePlotWindow();
	ScaleWindow* GetScaleWindow() { return m_scale; }
	void DeletePlot(PlotWindow *plot);

	void SetLeftButtonAction(LEFTBUTTON_ACTION lba);
private:

	wxSizer *m_sizer;
	ScaleWindow *m_scale;
	wxPanel *m_plotscontainer;

	wxAuiManager m_mgr;

	void OnPlotMenuItem_close(wxCommandEvent &event);
	//void OnPlotMenuItem_close_queued(wxCommandEvent &event);//for invoking plot deleteion in the next loop iteration to avoid crash of wxMenu
	static const int ID_PLOTMENUITEM_CLOSE;

	int m_orientation;
	void addplot(PlotWindow *plot);

	LEFTBUTTON_ACTION m_lbaction;

	DECLARE_EVENT_TABLE()

	//some helpers
	void close_plot_delayed(PlotWindow *plot);
};

