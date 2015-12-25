#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Space.h"
#include "Scale.h"
#include "Box.h"
////#include "Widget.h"


#include <vector>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Scale;
class WXDLLIMPEXP_PLOTLIB Box;
////class WXDLLIMPEXP_PLOTLIB Widget;


class WXDLLIMPEXP_PLOTLIB Plot
{
public:
	Plot(const char *plotname = NULL);
	void SetPlotName(const char *plotname = NULL);
	const char *GetPlotName() { return m_plot_name; }
	void AddSpace(SpaceND *space, bool update = true);
	std::vector<SpaceND *> &GetSpaces() { return m_spaces; }
	SpaceND *GetSpace(size_t indx);
	void Clear(bool update = true);
	void RemoveSpace(SpaceND *space, bool update = true);
	virtual ~Plot();
	virtual void RedrawPlot	() = 0;
	virtual void GetSize(int *width, int *height) = 0;
	void FitPlot(bool update = true);

	void SetCommonScale(Scale *scale);
	Scale *GetCommonScale() { return m_commonscale; }

	//void AddWidget(Widget *widget);
	//void DeleteWidget(Widget *widget);

	void SetLeftButtonAction(LEFTBUTTON_ACTION lba) { m_lbaction = lba; };
protected:

	void StartPan(double start_rx, double start_ry);
	void ProceedPan(double rx, double ry);
	void EndPan();

	void StartZoomSelect(double start_rx, double start_ry);
	void ProceedZoomSelect(double rx, double ry);
	void EndZoomSelect();
	virtual void DrawZoomSelection(double rx, double ry) = 0;
	double m_start_rx_zsel;
	double m_start_ry_zsel;
	double m_end_rx_zsel;
	double m_end_ry_zsel;

	void ZoomWheel(double rx, double ry, double xfactor, double yfactor);

	std::vector<SpaceND *> m_spaces;

	bool m_panning;

	bool m_zoomsel_switch;
	bool m_zoomselecting;

	char *m_plot_name;

	Scale *m_commonscale;

	std::vector<Box *> m_boxes;

	LEFTBUTTON_ACTION m_lbaction;

	//helpers
	void iterate_axes_redraw_uniq_commonscales_uniq_plots();

	friend class Box;
	void AddBox(Box *box);
	void DeleteBox(Box *box);
};

