//#include "stdafx.h"
#include "Plot.h"

static char *s_plotname = "plot";

Plot::Plot(const char *plotname)
{
	DPRINTF("Plot ctor\n");
	m_panning = false;

	if (plotname == NULL)
		m_plot_name = s_plotname;
	else
	{
		m_plot_name = (char *)malloc(strlen(plotname) + 1);
		strcpy(m_plot_name, plotname);
	}
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

	if (update)
		PlotUpdated();
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
	if (update)
		PlotUpdated();
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

	if (update)
	{
		PlotUpdated();
		
	}
}

void Plot::StartPan(double start_rx, double start_ry)
{
	DPRINTF("StartPan\n");
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
	for (auto space : m_spaces)
	{
		space->ProceedPanAt(rx, ry);
	}
}

void Plot::EndPan()
{
	DPRINTF("EndPan\n");
	for (auto space : m_spaces)
	{
		space->EndPanAt();
	}

	m_panning = false;
}

void Plot::ZoomWheel(double rx, double ry, double xfactor, double yfactor)
{
	DPRINTF("Zoom wheel\n");
	for (auto space : m_spaces)
	{
		space->ZoomAt(rx, ry, xfactor, yfactor);
	}
}


