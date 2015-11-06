//#include "stdafx.h"
#include "Area.h"


Area::Area()
{
	DPRINTF("Area ctor\n");
	m_owner_plot = NULL;
}

void Area::AddSeries(SeriesND * series, bool update)
{
#ifdef _DEBUG
	assert(series != NULL);
#endif
//	series->SetOwner(this);
	m_serie.push_back(series);
	if (update)
		AreaUpdated();
}

void Area::RemoveSeries(SeriesND * series, bool update)
{
	std::vector<SeriesND *> serie;
	for (auto * series_ : m_serie)
	{
		if (series == series_)
			continue;
		serie.push_back(series_);
	}
	m_serie = serie;
	if (update)
		AreaUpdated();
}

void Area::Clear(bool update)
{
	std::vector<SeriesND *> serie(m_serie);
	for (auto series : serie)
	{
		delete series;
	}
	m_serie.clear();
}

void Area::AreaUpdated()
{
	DPRINTF("Area updated\n");
	if (m_owner_plot != NULL)
		m_owner_plot->PlotUpdated();
}


Area::~Area()
{
	DPRINTF("Area dtor\n");
	Clear(false);
}
