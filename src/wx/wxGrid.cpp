#include <wx/graphics.h>

#include "wx/wxGrid.h"

using namespace plot;


wxGrid::wxGrid()
{
}

wxGrid::~wxGrid()
{
}

void wxGrid::Render(void * v_gc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	wxAntialiasMode antialiasmode = gc->GetAntialiasMode();
	gc->SetAntialiasMode(wxANTIALIAS_NONE);
	wxASSERT(m_owner != nullptr);
	//return;
	Axis *xaxis = m_owner->GetAxis(AXIS_X);
	Axis *yaxis = m_owner->GetAxis(AXIS_Y);

	wxASSERT(xaxis != nullptr && yaxis != nullptr);

	AxisAdaptor *xaxadaptor = nullptr;
	
	if(xaxis->_getcommonscale() != nullptr)
		xaxadaptor = xaxis->_getcommonscale()->GetValueAdaptor();//m_owner_space->GetOwner()->_getcommonscale()

	AxisAdaptor *yaxadaptor = nullptr;

	if(yaxis->_getcommonscale() != nullptr)
		yaxadaptor = yaxis->_getcommonscale()->GetValueAdaptor();
	

	//wxASSERT(yaxadaptor != nullptr);

	int width, height;
	m_owner->GetOwner()->GetSize(&width, &height);


	wxPen pen(*wxBLUE, 0, wxPENSTYLE_DOT);
	gc->SetPen(pen);

	if (xaxadaptor != nullptr)
	{
		xaxadaptor->InitState(xaxis->_getoffset(), xaxis->_getrange(), 15. / (double)width);
		while (xaxadaptor->Step())
		{
			double ticker = xaxadaptor->GetTicker();
			int x;
			x = (ticker) / xaxis->_getrange() * width;
			if (x < 0)
				continue;
			if (x > width)
				break;

			gc->StrokeLine(x, 0, x, height);
		}
	}

	if (yaxadaptor != nullptr)
	{
		yaxadaptor->InitState(yaxis->_getoffset(), yaxis->_getrange(), 15. / (double)height);
		while (yaxadaptor->Step())
		{
			double ticker = yaxadaptor->GetTicker();
			int y;
			y = (1 - (ticker) / yaxis->_getrange()) * height;
			if (y < 0)
				continue;
			if (y > height)
				break;

			gc->StrokeLine(0, y, width, y);
		}
	}

	gc->SetAntialiasMode(antialiasmode);
}