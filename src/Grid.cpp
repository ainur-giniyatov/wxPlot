#include "Grid.h"
#include "ChartWindow.h"

Grid::Grid(SpaceND *owner_space)
{
	m_owner_space = owner_space;
	m_owner_space->SetGrid(this);
}

Grid::~Grid()
{
}

void Grid::Render(wxGraphicsContext * gc)
{
	wxASSERT(m_owner_space != NULL);
	//return;
	Axis *xaxis = m_owner_space->GetAxis(AXIS_X);
	Axis *yaxis = m_owner_space->GetAxis(AXIS_Y);

	wxASSERT(xaxis != NULL && yaxis != NULL);

	AxisAdaptor *xaxadaptor = NULL;
	
	if(xaxis->GetCommonScale() != NULL)
		xaxadaptor = xaxis->GetCommonScale()->GetValueAdaptor();//m_owner_space->GetOwner()->GetCommonScale()

	AxisAdaptor *yaxadaptor = NULL;

	if(yaxis->GetCommonScale() != NULL)
		yaxadaptor = yaxis->GetCommonScale()->GetValueAdaptor();
	

	//wxASSERT(yaxadaptor != NULL);

	int width, height;
	m_owner_space->GetOwner()->GetSize(&width, &height);


	wxPen pen(*wxBLUE, 0, wxPENSTYLE_DOT);
	gc->SetPen(pen);

	if (xaxadaptor != NULL)
	{
		xaxadaptor->InitState(xaxis->GetOffset(), xaxis->GetRange(), 15. / (double)width);
		while (xaxadaptor->Step())
		{
			double ticker = xaxadaptor->GetTicker();
			int x;
			x = (ticker) / xaxis->GetRange() * width;
			if (x < 0)
				continue;
			if (x > width)
				break;

			gc->StrokeLine(x, 0, x, height);
		}
	}

	if (yaxadaptor != NULL)
	{
		yaxadaptor->InitState(yaxis->GetOffset(), yaxis->GetRange(), 15. / (double)height);
		while (yaxadaptor->Step())
		{
			double ticker = yaxadaptor->GetTicker();
			int y;
			y = (1 - (ticker) / yaxis->GetRange()) * height;
			if (y < 0)
				continue;
			if (y > height)
				break;

			gc->StrokeLine(0, y, width, y);
		}
	}
}

void Grid::GridUpdated()
{
}
