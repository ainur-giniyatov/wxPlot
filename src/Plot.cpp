//#include "stdafx.h"
#include "Plot.h"
//#include "ScaleWidget.h"
#include <algorithm>
#include <math.h>

static char *s_plotname = "plot";

Plot::Plot(const char *plotname)
{
	DPRINTF("Plot ctor\n");
	m_panning = false;
	m_zoomselecting = false;
	m_zoomsel_switch = false;
	m_commonscale = NULL;
	if (plotname == NULL)
		m_plot_name = s_plotname;
	else
	{
		m_plot_name = (char *)malloc(strlen(plotname) + 1);
		strcpy(m_plot_name, plotname);
	}

	m_lbaction = LBA_ZOOMSELECT;

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

void Plot::AddSpace(SpaceND * space, bool update)
{
	assert(space != NULL);
	space->SetOwner(this);
	m_spaces.push_back(space);

	//if (update)
	//	PlotUpdated();
}

SpaceND * Plot::GetSpace(size_t indx)
{
	wxASSERT(indx < m_spaces.size());

	return m_spaces[indx];
}

void Plot::Clear(bool update)
{
}

void Plot::RemoveSpace(SpaceND * space, bool update)
{
	std::vector<SpaceND *> spaces;
	for (auto space_ : m_spaces)
	{
		if (space == space_)
			continue;
		spaces.push_back(space_);
	}
	m_spaces = spaces;
	//if (update)
	//	PlotUpdated();
}



Plot::~Plot()
{
	DPRINTF("Plot dtor\n");
	std::vector<SpaceND *> spaces(m_spaces);
	for (auto space : spaces)
	{
		space->SetOwner(NULL);
		delete space;
	}

	if (m_plot_name != NULL && m_plot_name != s_plotname)
		free(m_plot_name);

	for (auto box : m_boxes)
		delete box;
}

void Plot::FitPlot(bool update)
{
	if (m_spaces.empty())
		return;

	//TO DO correct for fitting all spaces alltogether
//	for (auto space : m_spaces)
//	{
		m_spaces[0]->Fit(false);
		m_spaces[0]->GetAxis(AXIS_X)->AxisUpdated();
		m_spaces[0]->GetAxis(AXIS_Y)->AxisUpdated();
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

/*for internal use. called from box ctor*/
void Plot::AddBox(Box *box)
{
	if (std::any_of(m_boxes.begin(), m_boxes.end(), [box](Box *b) { return b == box; }))
	{
		return;
	}

	m_boxes.push_back(box);

	RedrawPlot();
}

void Plot::DeleteBox(Box *box)
{
	TODO
	std::vector<Box *> boxes;
	for (auto boxi : m_boxes)
	{
		if (boxi != box)
			boxes.push_back(boxi);
		else
			 delete box;
	}

	m_boxes = boxes;

	RedrawPlot();
}

void Plot::StartPan(double start_rx, double start_ry)
{
	DPRINTF("StartPan\n");
	wxASSERT(!m_panning);
	for (auto space : m_spaces)
	{
		space->StartPanAt(start_rx, start_ry);
	}

	m_panning = true;
}

void Plot::ProceedPan(double rx, double ry)
{
	if (!m_panning)
		return;

	DPRINTF("ProceedPan\n");

	//in this method new range & offsets are calculated and propagated to common scale
	for (auto space : m_spaces)
	{
		space->ProceedPanAt(rx, ry);
	}

	iterate_axes_redraw_uniq_commonscales_uniq_plots();
	//RedrawPlot();//redraw for this plot shall be invoked in iterate_axes_redraw_uniq_commonscales_uniq_plots

}

void Plot::EndPan()
{
	DPRINTF("EndPan\n");

	if (!m_panning)
		return;

	for (auto space : m_spaces)
	{
		space->EndPanAt();
	}

	m_panning = false;
}

void Plot::StartZoomSelect(double start_rx, double start_ry)
{
	DPRINTF("Plot::StartZoomSelect\n");
	//wxASSERT(!m_zoomselecting);

	m_start_rx_zsel = start_rx;
	m_start_ry_zsel = start_ry;

	m_zoomsel_switch = true;
	m_zoomselecting = false;
}

void Plot::ProceedZoomSelect(double rx, double ry)
{
	DPRINTF("Plot::ProceedZoomSelect\n");

	m_end_rx_zsel = rx;
	m_end_ry_zsel = ry;

	int width, height, xd, yd;
	GetSize(&width, &height);

	xd = abs((rx - m_start_rx_zsel) * width);
	yd = abs((ry - m_start_ry_zsel) * height);

	if (m_zoomselecting)
	{
		DrawZoomSelection(rx, ry);
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
		for (auto space : m_spaces)
		{
			space->ZoomSelection(m_start_rx_zsel, m_start_ry_zsel, m_end_rx_zsel, m_end_ry_zsel);
		}
	}

	//RedrawPlot();
	iterate_axes_redraw_uniq_commonscales_uniq_plots();
	m_zoomselecting = false;
	m_zoomsel_switch = false;
}

void Plot::ZoomWheel(double rx, double ry, double xfactor, double yfactor)
{
	DPRINTF("Zoom wheel\n");
	for (auto space : m_spaces)
	{
		space->ZoomAt(rx, ry, xfactor, yfactor);
	}


	iterate_axes_redraw_uniq_commonscales_uniq_plots();
	//RedrawPlot();//redraw for this plot shall be invoked in iterate_axes_redraw_uniq_commonscales_uniq_plots
}

void Plot::iterate_axes_redraw_uniq_commonscales_uniq_plots()
{
	//here all axises are iterated in each space and common scale is redrawn. common scales must be updated once
	std::vector<Scale *> vcommscales;
	std::vector<Plot *> vuniqplots;
	bool this_updated = false;
	for (auto space : m_spaces)
	{
		for (size_t indx = 0; indx < space->GetDimsCount(); indx++)
		{
			Axis *axis = space->GetAxis((AXIS_DIR)indx);
			wxASSERT(axis != NULL);
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


