#include <algorithm>
#include <math.h>
#include <assert.h>
#include <string>
#include <string.h>

#include "Plot.h"

using namespace plot;

static char *s_plotname = "plot";

Plot::Plot(const char *plotname)
{
	DPRINTF("Plot ctor\n");
	m_panning = false;
	m_zoomselecting = false;
	m_zoomsel_switch = false;
	m_commonscale = NULL;
	m_is_data_view_modified = true;

	if (plotname == NULL)
		m_plot_name = s_plotname;
	else
	{
		m_plot_name = (char *)malloc(strlen(plotname) + 1);
		strcpy(m_plot_name, plotname);
	}

	m_lbaction = LBA_ZOOMSELECT;

	m_eventslist = new PEventList();
}

void Plot::SetPlotName(const char * plotname)
{
	if (m_plot_name != NULL && m_plot_name != s_plotname)
		free(m_plot_name);

	if (plotname == NULL)
		m_plot_name = s_plotname;
	else
	{
		m_plot_name = (char *)malloc(strlen(plotname) + 1);
		strcpy(m_plot_name, plotname);
	}
}

void Plot::AddArea(Area * area)
{
	if (std::none_of(m_areas.begin(), m_areas.end(), [area](Area *a) {return area == a; }))
	{
		m_areas.push_back(area);
		area->_SetOwner(this);

		for (auto series : area->GetSerie())
		{
			PEventSeriesAdded *evt = new PEventSeriesAdded();
			evt->SetSeries(series);
			m_eventslist->ProcessEvent(evt);
		}
		RedrawPlot();
	}
}
void Plot::RemoveArea(Area * area)
{
	for (auto areas_iter = m_areas.begin(); areas_iter != m_areas.end(); ++areas_iter)
	{
		if (*areas_iter == area)
		{
			m_areas.erase(areas_iter);
			break;
		}
	}
}

void Plot::DeleteArea(Area * area)
{
	for (auto areas_iter = m_areas.begin(); areas_iter != m_areas.end(); ++areas_iter)
	{
		if (*areas_iter == area)
		{
			m_areas.erase(areas_iter);
			delete area;
			break;
		}
	}

}

void Plot::Clear(bool update)
{
}

Plot::~Plot()
{
	DPRINTF("Plot dtor\n");
	std::vector<Area *> areas(m_areas);
	for (auto area : areas)
	{
		delete area;
	}

	if (m_plot_name != NULL && m_plot_name != s_plotname)
		free(m_plot_name);

	for (auto box : m_boxes)
		delete box;

	delete m_eventslist;
}

void Plot::FitPlot(bool update)
{
	if (m_areas.empty())
		return;

	//TO DO correct for fitting all spaces alltogether
//	for (auto space : m_spaces)
//	{
		//m_spaces[0]->Fit(false);
		//m_spaces[0]->GetAxis(AXIS_X)->AxisUpdated();
		//m_spaces[0]->GetAxis(AXIS_Y)->AxisUpdated();
		/*for (auto series : space->GetSerie())
		{
			for (auto data : series->GetDatas())
			{

			}
		}*/
//	}

	//if (update)
	//{
	//	PlotUpdated();
	//
	//}
}

void Plot::SetCommonScale(Scale * scale)
{
	m_commonscale = scale;
}

void Plot::RemoveBox(Box * box)
{
	for (auto box_iter = m_boxes.begin(); box_iter != m_boxes.end(); ++box_iter)
	{
		if (*box_iter == box)
		{
			m_boxes.erase(box_iter);
			break;
		}
	}
}

void Plot::DeleteBox(Box * box)
{
	for (auto box_iter = m_boxes.begin(); box_iter != m_boxes.end(); ++box_iter)
	{
		if (*box_iter == box)
		{
			m_boxes.erase(box_iter);
			delete box;
			break;
		}
	}
}

/*for internal use. called from box ctor*/
void Plot::AddBox(Box *box)
{
	if (std::any_of(m_boxes.begin(), m_boxes.end(), [box](Box *b) { return b == box; }))
	{
		return;
	}

	m_boxes.push_back(box);

}

void Plot::_SetViewModifiedFlag()
{
	m_is_data_view_modified = true;
}

void Plot::StartPan(const Point<double> &pan_start_rel_coord)
{
	DPRINTF("StartPan\n");
	assert(!m_panning);
	//for (auto space : m_spaces)
	//{
	//	space->StartPanAt(start_rx, start_ry);
	//}

	for (auto area : m_areas)
	{
		area->StartPan(pan_start_rel_coord);
	}
	m_panning = true;
}

void Plot::ProceedPan(const Point<double> &pan_proceed_rel_coord)
{
	DPRINTF("ProceedPan\n");
	if (!m_panning)
		return;


	for (auto area : m_areas)
		area->ProceedPan(pan_proceed_rel_coord);
	
	iterate_axes_redraw_uniq_commonscales_uniq_plots();
}

void Plot::EndPan()
{
	DPRINTF("EndPan\n");

	if (!m_panning)
		return;

	for (auto area: m_areas)
		area->EndPan();

	m_panning = false;
}

void Plot::StartZoomSelect(const Point<double> &zoom_sel_start_rel_coord)
{
	DPRINTF("Plot::StartZoomSelect\n");
	assert(!m_zoomselecting);

	m_zoom_sel_start_rel_coord = zoom_sel_start_rel_coord;
	m_zoomsel_switch = true;
	m_zoomselecting = false;
}

void Plot::ProceedZoomSelect(const Point<double> &zoom_sel_proceed_rel_coord)
{
	DPRINTF("Plot::ProceedZoomSelect\n");

	m_zoom_sel_end_rel_coord = zoom_sel_proceed_rel_coord;
	int width, height, xd, yd;
	GetSize(&width, &height);

	xd = abs((m_zoom_sel_end_rel_coord.x - m_zoom_sel_start_rel_coord.x) * width);
	yd = abs((m_zoom_sel_end_rel_coord.y - m_zoom_sel_start_rel_coord.y) * height);

	if (m_zoomselecting)
	{
		DrawZoomSelection();
		if (xd < 10 || yd < 10)
		{
			iterate_axes_redraw_uniq_commonscales_uniq_plots();
			m_zoomselecting = false;
			m_zoomsel_switch = false;
		}
	}
	else
	{
		if (m_zoomsel_switch && (xd > 10 && yd > 10))
		{
			m_zoomselecting = true;
			m_zoomsel_switch = false;
		}
	}

}

void Plot::EndZoomSelect()
{
	DPRINTF("Plot::EndZoomSelect\n");
	if (!m_zoomselecting && !m_zoomsel_switch)
		return;

	if (m_zoomselecting)
	{
		for (auto area : m_areas)
		{
			area->ZoomSelection(m_zoom_sel_start_rel_coord, m_zoom_sel_end_rel_coord);
		}
		//for (auto space : m_spaces)
		//{
		//	space->ZoomSelection(m_start_rx_zsel, m_start_ry_zsel, m_end_rx_zsel, m_end_ry_zsel);
		//}
	}

//	RedrawPlot();
	iterate_axes_redraw_uniq_commonscales_uniq_plots();
	m_zoomselecting = false;
	m_zoomsel_switch = false;
}

void Plot::Zoom(const Point<double> &zoom_wheel_rel_coord, double xfactor, double yfactor)
{
	DPRINTF("Zoom wheel\n");

	for (auto area : m_areas)
		area->Zoom(zoom_wheel_rel_coord, xfactor, yfactor);

	iterate_axes_redraw_uniq_commonscales_uniq_plots();
}

void Plot::iterate_axes_redraw_uniq_commonscales_uniq_plots()
{
	//here all axes are iterated in each area and common scale is redrawn. common scales must be updated once
	
	std::vector<Scale *> vcommscales;
	std::vector<Plot *> vuniqplots;
	bool this_updated = false;
	for (auto area : m_areas)
	{
		for (size_t indx = 0; area->GetAxis((AXIS_DIR)indx) != nullptr; indx++)
		{
			Axis *axis = area->GetAxis((AXIS_DIR)indx);
			assert(axis != NULL);
			Scale *commonscale = axis->GetCommonScale();
			if (commonscale != NULL && std::count(vcommscales.begin(), vcommscales.end(), commonscale) == 0)
			{
				commonscale->ScaleRedraw();
				vcommscales.push_back(commonscale);

				for (auto axisi : commonscale->GetAxes())
				{
					Plot *plot = axisi->GetOwner()->GetOwner();
					if (std::count(vuniqplots.begin(), vuniqplots.end(), plot) == 0)
					{
						if (this == plot)
							this_updated = true;
						plot->_SetViewModifiedFlag();
						plot->RedrawPlot();
						vuniqplots.push_back(plot);
					}
				}
			}
		}
	}
	if(!this_updated)
		RedrawPlot();//redraw directly if not bound to any common scale
}

const int PEventSeriesAdded::s_event_id = PEventList::GetNewEventId();

plot::PEventSeriesAdded::PEventSeriesAdded()
{
	m_event_id = s_event_id;
	m_addedoremoved = true;
}

plot::PEventSeriesAdded::~PEventSeriesAdded()
{
}

const int PEventAreaAdded::s_event_id = PEventList::GetNewEventId();

plot::PEventAreaAdded::PEventAreaAdded()
{
	m_event_id = s_event_id;
}

plot::PEventAreaAdded::~PEventAreaAdded()
{
}
