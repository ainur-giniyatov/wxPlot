#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Plot.h"
#include "Scale.h"
#include "ValueAdaptor.h"
#include "Grid.h"

#include <vector>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB Grid;


class WXDLLIMPEXP_PLOTLIB SpaceND
{
public:
	SpaceND(size_t dims_count);
	virtual ~SpaceND();

	Axis *GetAxis(AXIS_DIR axis_dir);

	size_t GetDimsCount() { return m_dims_count; }
	void AddSeries(SeriesND *series, bool update = true);
	void RemoveSeries(SeriesND *series, bool update = true);

	void Clear(bool update = true);

	void SpaceUpdated();
	void SetOwner(Plot *plot) { m_owner_plot = plot; }
	Plot *GetOwner() { return m_owner_plot; }

	std::vector<SeriesND *> &GetSerie() { return m_serie; }

	void ZoomAt(double rx, double ry, double xfactor, double yfactor);
	void StartPanAt(double rx, double ry);
	void ProceedPanAt(double rx, double ry);
	void EndPanAt();
	void Fit(bool update = true);

	Scale *GetYScale() { return m_yscale; };
	Grid *GetGrid() { return m_grid; };
protected:
	std::vector<SeriesND *> m_serie;
	Axis ** m_axes;

	Plot *m_owner_plot;

	double m_pan_start_at_rx;
	double m_pan_start_at_ry;
	double m_pan_start_at_vx;
	double m_pan_start_at_vy;

	size_t m_dims_count;//count of dimensions in this space

	Scale *m_yscale;

	Grid *m_grid;
private:

};


//TO DO: redesign Spaces concept