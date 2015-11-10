#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Space.h"
#include "Scale.h"

#include <vector>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Scale;

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
	virtual void PlotUpdated() = 0;
	virtual void GetSize(int *width, int *height) = 0;
	void FitPlot(bool update = true);
	virtual Scale *GetCommonScale() = 0;
protected:

	void StartPan(double start_rx, double start_ry);
	void ProceedPan(double rx, double ry);
	void EndPan();

	void ZoomWheel(double rx, double ry, double xfactor, double yfactor);

	std::vector<SpaceND *> m_spaces;

	bool m_panning;

	char *m_plot_name;

	//helpers
	
};

