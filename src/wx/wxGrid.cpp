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
//	wxASSERT(m_owner != nullptr);
	//return;
	//Axis *xaxis = m_owner->GetAxis(AXIS_X);
	//Axis *yaxis = m_owner->GetAxis(AXIS_Y);

	//wxASSERT(xaxis != nullptr && yaxis != nullptr);

	//AxisAdaptor *xaxadaptor = nullptr;
	//
	//if(xaxis->_getcommonscale() != nullptr)
	//	xaxadaptor = xaxis->_getcommonscale()->GetValueAdaptor();

	//AxisAdaptor *yaxadaptor = nullptr;

	//if(yaxis->_getcommonscale() != nullptr)
	//	yaxadaptor = yaxis->_getcommonscale()->GetValueAdaptor();
	//

	////wxASSERT(yaxadaptor != nullptr);

	//int width, height;
	//auto size = m_owner->GetOwner()->_get_size();
	//width = size.w;
	//height = size.h;


	//wxPen pen(*wxBLUE, 0, wxPENSTYLE_DOT);
	//gc->SetPen(pen);

	//if (xaxadaptor != nullptr)
	//{
	//	xaxadaptor->InitState(xaxis->_getoffset(), xaxis->_getrange(), 15. / (double)width);
	//	while (xaxadaptor->MajorStep())
	//	{
	//		double ticker = xaxadaptor->GetTicker();
	//		int x;
	//		x = (ticker) / xaxis->_getrange() * width;
	//		if (x < 0)
	//			continue;
	//		if (x > width)
	//			break;

	//		if(m_owner->GetOwner()->_get_orientation() == Plot::ORIENTATION_NORMAL)
	//			gc->StrokeLine(x, 0, x, height);
	//		else
	//			gc->StrokeLine(0, x, height, x);
	//	}
	//}

	//if (yaxadaptor != nullptr)
	//{
	//	yaxadaptor->InitState(yaxis->_getoffset(), yaxis->_getrange(), 15. / (double)height);
	//	while (yaxadaptor->MajorStep())
	//	{
	//		double ticker = yaxadaptor->GetTicker();
	//		int y;
	//		y = (ticker) / yaxis->_getrange() * height;
	//		if (y < 0)
	//			continue;
	//		if (y > height)
	//			break;

	//		if (m_owner->GetOwner()->_get_orientation() == Plot::ORIENTATION_NORMAL)
	//			gc->StrokeLine(0, height - y + 1, width, height - y + 1);
	//		else
	//			gc->StrokeLine(y, width, y, 0);
	//	}
	//}

	gc->SetAntialiasMode(antialiasmode);
}