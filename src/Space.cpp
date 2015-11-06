//#include "stdafx.h"
#include "Space.h"


void SpaceND::AddSeries(SeriesND * series, bool update)
{
#ifdef _DEBUG
	wxASSERT(series != NULL);
#endif
	series->SetOwner(this);
	m_serie.push_back(series);
	if (update)
		SpaceUpdated();
}

void SpaceND::RemoveSeries(SeriesND * series, bool update)
{
	std::vector<SeriesND *> serie;
	for (auto series_ : m_serie)
	{
		if (series == series_)
		{
			continue;
		}
		serie.push_back(series_);
	}
	m_serie = serie;

	if (update)
		SpaceUpdated();
}

void SpaceND::Clear(bool update)
{
	std::vector<SeriesND *> serie(m_serie);

//delete series
	for (auto series : serie)
	{
		series->SetOwner(NULL);
		delete series;
	}

	m_serie.clear();

	if (update)
		SpaceUpdated();
}

void SpaceND::SpaceUpdated()
{
	DPRINTF("Space updated\n");
	if (m_owner_plot != NULL)
		m_owner_plot->PlotUpdated();
}

SpaceND::SpaceND(size_t dims_count)
{
	DPRINTF("SpaceND ctor\n");
	wxASSERT(dims_count > 0);//can not be zero of cause
	wxASSERT(dims_count == 2);//only 2D available for now, have to modify screen-to-space conversion routines
	
	m_owner_plot = NULL;

	m_dims_count = dims_count;

	m_axes = (Axis **)malloc(sizeof(Axis *) * m_dims_count);
	for (size_t indx = 0; indx < m_dims_count; indx++)
	{
		m_axes[indx] = new Axis();
		m_axes[indx]->SetOwner(this);
	}
}

SpaceND::~SpaceND()
{
	DPRINTF("SpaceND dtor\n");


//delete all serie
	Clear(false);

//delete all axes
	for (size_t indx = 0; indx < m_dims_count; indx++)
		delete m_axes[indx];
	
	free(m_axes);

	if (m_owner_plot != NULL)
		m_owner_plot->RemoveSpace(this, true);


}

Axis * SpaceND::GetAxis(AXIS_DIR axis_dir)
{
	wxASSERT(axis_dir < m_dims_count);
	return m_axes[axis_dir];
}

//screen-to-space, done for 2D for now
void SpaceND::ZoomAt(double rx, double ry, double xfactor, double yfactor)
{
	DPRINTF("ZoomAt\n");
	Axis *m_xaxis;
	Axis *m_yaxis;
	m_xaxis = m_axes[0];//let x be 1st dimension
	m_yaxis = m_axes[1];//let y be 2nd dimension

	double offs, range, x, y;
	range = m_xaxis->GetRange();
	offs = m_xaxis->GetOffset();
	x = offs + range * rx;
	if (m_xaxis->GetCommonScale() != NULL)
	{
		if (m_xaxis->GetCommonScale()->IsInRange(range * xfactor))
		{
			m_xaxis->SetOffset(x - (x - offs) * xfactor);
			m_xaxis->SetRange(range * xfactor);
		}
	}
	else
	{
		m_xaxis->SetOffset(x - (x - offs) * xfactor);
		m_xaxis->SetRange(range * xfactor);
	}

	
	range = m_yaxis->GetRange();
	offs = m_yaxis->GetOffset();
	y = offs + range * ry;
	if (m_yaxis->GetCommonScale() != NULL)
	{
		if (m_yaxis->GetCommonScale()->IsInRange(range * yfactor))
		{
			m_yaxis->SetOffset(y - (y - offs) * yfactor);
			m_yaxis->SetRange(range * yfactor);
		}
	}
	else
	{
		m_yaxis->SetOffset(y - (y - offs) * yfactor);
		m_yaxis->SetRange(range * yfactor);
	}


	if (m_xaxis != NULL && xfactor != 1.)
		m_xaxis->AxisUpdated();
	else
		SpaceUpdated();
}

void SpaceND::StartPanAt(double rx, double ry)
{
	DPRINTF("SpaceND::StartPanAt\n");

	Axis *m_xaxis;
	Axis *m_yaxis;
	m_xaxis = m_axes[0];//let x be 1st dimension
	m_yaxis = m_axes[1];//let y be 2nd dimension

	m_pan_start_at_rx = rx;
	m_pan_start_at_ry = ry;

	if (m_xaxis != NULL)
		m_pan_start_at_vx = m_xaxis->GetOffset();

	if (m_yaxis != NULL)
		m_pan_start_at_vy = m_yaxis->GetOffset();
}

void SpaceND::ProceedPanAt(double rx, double ry)
{
	DPRINTF("SpaceND::ProceedPanAt\n");

	Axis *m_xaxis;
	Axis *m_yaxis;
	m_xaxis = m_axes[0];//let x be 1st dimension
	m_yaxis = m_axes[1];//let y be 2nd dimension

	if (m_xaxis != NULL)
		m_xaxis->SetOffset(m_pan_start_at_vx - m_xaxis->GetRange() * (rx - m_pan_start_at_rx));


	if (m_yaxis != NULL)
		m_yaxis->SetOffset(m_pan_start_at_vy - m_yaxis->GetRange() * (ry - m_pan_start_at_ry));

	if (m_xaxis != NULL)
		m_xaxis->AxisUpdated();
	else
		SpaceUpdated();
}

void SpaceND::EndPanAt()
{
	DPRINTF("SpaceND::EndPanAt\n");
}

void SpaceND::Fit(bool update)
{
	for (size_t dir = 0; dir < m_dims_count; dir++)
	{
		double max, min;
		max = m_serie[0]->GetNData((AXIS_DIR)dir)->GetDataMax();
		min = m_serie[0]->GetNData((AXIS_DIR)dir)->GetDataMin();
		for (auto series : m_serie)
		{
			if (max < series->GetNData((AXIS_DIR)dir)->GetDataMax())
				max = series->GetNData((AXIS_DIR)dir)->GetDataMax();
			if (min > series->GetNData((AXIS_DIR)dir)->GetDataMin())
				min = series->GetNData((AXIS_DIR)dir)->GetDataMin();
		}

		m_axes[dir]->SetVisibleRange(min, max - min, false);

	}
	if (update)
		SpaceUpdated();
}
