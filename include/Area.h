#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Plot.h"
#include <vector>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB Plot;


class WXDLLIMPEXP_PLOTLIB Area
{
public:
	Area();
	virtual ~Area();

	void AddSeries(SeriesND *series, bool update = true);
	void RemoveSeries(SeriesND *series, bool update = true);
	void Clear(bool update = true);

	void AreaUpdated();
	void SetOwner(Plot *plot) { m_owner_plot = plot; }
	Plot *GetOwner() { return m_owner_plot; }

	std::vector<SeriesND *> &GetSerie() { return m_serie; }

protected:
	std::vector<SeriesND *> m_serie;
	Plot *m_owner_plot;

private:


};

//class WXDLLIMPEXP_PLOTLIB AreaScaleable: public Area
//{
//public:
//	AreaScaleable();
//	virtual ~AreaScaleable();
//
//protected:
//
//private:
//};
