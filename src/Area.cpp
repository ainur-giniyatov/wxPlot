#include<algorithm>
#include <assert.h>

#include "Area.h"

using namespace plot;

Area::Area(int dim_num)
{
	DPRINTF("Area ctor\n");
	m_owner_plot = NULL;
	m_grid = NULL;

	m_dim_num = dim_num;
	assert(m_dim_num > 0 && m_dim_num < 3);

	m_axes = (Axis **)malloc(sizeof(Axis *) * m_dim_num);
	for (int indx = 0; indx < m_dim_num; indx++)
	{
		Axis *axis;
		axis = new Axis((AXIS_DIR)indx);
		axis->SetOwner(this);
		m_axes[indx] = axis;
	}

}

Area::~Area()
{
	DPRINTF("Area dtor\n");
	
	if (m_grid != NULL)
		delete m_grid;

	std::vector<Series *> serie(m_serie);
	for (auto series : serie)
	{
		delete series;
	}

	for (int indx = 0; indx < m_dim_num; indx++)
	{
		Axis *axis;
		axis = m_axes[indx];
		delete axis;
	}

	free(m_axes);
}

void Area::AddSeries(Series * series)
{
	if (std::none_of(m_serie.begin(), m_serie.end(), [series](Series *z) {return z == series; }))
	{
		series->_setowner(this);
		m_serie.push_back(series);
		if (m_owner_plot != nullptr)
		{
			m_owner_plot->HandleEvent(PEventSeriesAdded(series, true));
		}
	}
}

void Area::RemoveSeries(Series * series)
{
	for (auto series_iter = m_serie.begin(); series_iter != m_serie.end(); ++series_iter)
	{
		if (*series_iter == series)
		{
			m_serie.erase(series_iter);
			m_owner_plot->HandleEvent(PEventSeriesAdded(series, false));
			break;
		}
	}
}

void plot::Area::DeleteSeries(Series * series)
{
	for (auto series_iter = m_serie.begin(); series_iter != m_serie.end(); ++series_iter)
	{
		if (*series_iter == series)
		{
			m_serie.erase(series_iter);
			m_owner_plot->HandleEvent(PEventSeriesAdded(series, false));
			delete series;
			break;
		}
	}
}

Axis * Area::GetAxis(AXIS_DIR axis_dir)
{
	return axis_dir < m_dim_num ? m_axes[axis_dir] : nullptr;
}

//void Area::Zoom(const Point<double>& zoom_wheel_rel_coord, double xfactor, double yfactor)
//{
//}
//
//void Area::StartPan(const Point<double>& pan_start_rel_coord)
//{
//}
//
//void Area::ProceedPan(const Point<double>& pan_proceed_rel_coord)
//{
//}
//
//void Area::EndPan()
//{
//}
//
//void Area::ZoomSelection(double start_rx, double start_ry, double end_rx, double end_ry)
//{
//}

const std::vector<Axis*> plot::Area::_get_axes()
{
	std::vector<Axis*> axes;
	for (int indx = 0; indx < m_dim_num; indx++)
	{
		if (m_axes[indx] != nullptr)
			axes.push_back(m_axes[indx]);
	}
	return axes;
}

void plot::Area::_SetOwner(Plot * plot)
{
	m_owner_plot = plot;
	if (m_owner_plot != nullptr)
	{
		int w, h;
		m_owner_plot->GetSize(&w, &h);
		for (auto series : m_serie)
			if (series->GetRenderer() != nullptr)
				series->GetRenderer()->_setsize(w, h);
	}
}

void Area::_SetGrid(Grid * grid)
{
	if (m_grid != NULL && grid != nullptr)
		delete m_grid;

	m_grid = grid;
}

//void Area::update_uniq_plots()
//{
//	std::vector<Plot *> uniq_plots;
//	for (int indx = 0; indx < m_dim_num; indx++)
//	{
//		Axis *axis;
//		axis = m_axes[indx];
//		if (axis == nullptr)
//			continue;
//		Plot *plot;
//		plot = axis->GetOwner()->GetOwner();
//		if (std::none_of(uniq_plots.begin(), uniq_plots.end(), [plot](Plot *p) {return plot == p; }))
//		{
//			plot->_SetViewModifiedFlag();
//			plot->RedrawPlot();
//			uniq_plots.push_back(plot);
//		}
//
//	}
//}

//Area2D::Area2D()
//{
//	m_xaxis = new Axis();
//	m_yaxis = new Axis();
//
//	m_xaxis->SetOwner(this);
//	m_yaxis->SetOwner(this);
//}
//
//Area2D::~Area2D()
//{
//	delete m_xaxis;
//	delete m_yaxis;
//}

//void Area::Zoom(const Point<double>& zoom_wheel_rel_coord, double xfactor, double yfactor)
//{
//	DPRINTF("ZoomAt\n");
//	Axis *xaxis;
//	Axis *yaxis;
//	xaxis = GetAxis(AXIS_X);
//	yaxis = GetAxis(AXIS_Y);
//
//	double offs, range, x, y;
//	range = xaxis->GetRange();
//	offs = xaxis->GetOffset();
//	x = offs + range * zoom_wheel_rel_coord.x;
//	if (xaxis->GetCommonScale() != NULL)
//	{
//		if (xaxis->GetCommonScale()->IsInRange(range * xfactor))
//		{
//			xaxis->SetOffset(x - (x - offs) * xfactor);
//			xaxis->SetRange(range * xfactor);
//		}
//	}
//	else
//	{
//		xaxis->SetOffset(x - (x - offs) * xfactor);
//		xaxis->SetRange(range * xfactor);
//	}
//
//	range = yaxis->GetRange();
//	offs = yaxis->GetOffset();
//	y = offs + range * zoom_wheel_rel_coord.y;
//	if (yaxis->GetCommonScale() != NULL)
//	{
//		if (yaxis->GetCommonScale()->IsInRange(range * yfactor))
//		{
//			yaxis->SetOffset(y - (y - offs) * yfactor);
//			yaxis->SetRange(range * yfactor);
//		}
//	}
//	else
//	{
//		yaxis->SetOffset(y - (y - offs) * yfactor);
//		yaxis->SetRange(range * yfactor);
//	}
//
//	m_owner_plot->_SetViewModifiedFlag();
//}
//
//void Area::StartPan(const Point<double>& pan_start_rel_coord)
//{
//	m_pan_start_rel_coord = pan_start_rel_coord;
//	m_pan_start_axes_offset.x = GetAxis(AXIS_X)->GetOffset();
//	m_pan_start_axes_offset.y = GetAxis(AXIS_Y)->GetOffset();
//}
//
//void Area::ProceedPan(const Point<double>& pan_proceed_rel_coord)
//{
//	Point<double> pdiff;
//	pdiff = m_pan_start_rel_coord - pan_proceed_rel_coord;
//	GetAxis(AXIS_X)->SetOffset(m_pan_start_axes_offset.x + pdiff.x * GetAxis(AXIS_X)->GetRange());
//	GetAxis(AXIS_Y)->SetOffset(m_pan_start_axes_offset.y + pdiff.y * GetAxis(AXIS_Y)->GetRange());
//
//
//
//}
//
//void Area::EndPan()
//{
//}
//
//void Area::ZoomSelection(Point<double>& start_p, Point<double>& end_p)
//{
//	DPRINTF("Area::ZoomSelection\n");
//
//	Axis *xaxis;
//	Axis *yaxis;
//	xaxis = m_axes[AXIS_X]; //let x be 1st dimension
//	yaxis = m_axes[AXIS_Y]; //let y be 2nd dimension
//	double start_rx, end_rx, start_ry, end_ry;
//	start_rx = start_p.x;
//	end_rx = end_p.x;
//	start_ry = start_p.y;
//	end_ry = end_p.y;
//
//	double temp;
//	temp = start_rx;
//	if (start_rx > end_rx)
//	{
//		start_rx = end_rx;
//		end_rx = temp;
//	}
//
//	temp = start_ry;
//	if (start_ry > end_ry)
//	{
//		start_ry = end_ry;
//		end_ry = temp;
//	}
//
//	//TO DO: need to review this code
//	if (xaxis != NULL)
//	{
//		//xaxis->SetOffset(m_pan_start_at_vx - xaxis->GetRange() * (rx - m_pan_start_at_rx));
//		xaxis->SetOffset(xaxis->GetOffset() + xaxis->GetRange() * start_rx);
//		xaxis->SetRange(xaxis->GetRange() * (end_rx - start_rx));
//	}
//
//
//	if (yaxis != NULL)
//	{
//		//yaxis->SetOffset(m_pan_start_at_vy - yaxis->GetRange() * (ry - m_pan_start_at_ry));
//		yaxis->SetOffset(yaxis->GetOffset() + yaxis->GetRange() * start_ry);
//		yaxis->SetRange(yaxis->GetRange() * (end_ry - start_ry));
//	}
//
//}
//
//
