//#include "stdafx.h"
#include "PlotWindow.h"
#include "ChartWindow.h"

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(PlotWindow, wxWindow)
EVT_PAINT(PlotWindow::OnPaint)
EVT_ERASE_BACKGROUND(PlotWindow::OnEraseBackground)
EVT_SIZE(PlotWindow::OnResize)
EVT_MOUSEWHEEL(PlotWindow::OnMouseWheel)
EVT_LEFT_DOWN(PlotWindow::OnLeftDown)
EVT_LEFT_UP(PlotWindow::OnLeftUp)
EVT_MOTION(PlotWindow::OnMouseMove)
END_EVENT_TABLE()


PlotWindow::PlotWindow(wxWindow * parent) :wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER)
{
	DPRINTF("PlotWindow: ctor\n");
	SetName("plot");
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_sizer = new wxBoxSizer(wxHORIZONTAL);


	SetSizer(m_sizer);
	Layout();
}

PlotWindow::~PlotWindow()
{
	DPRINTF("PlotWindow: dtor\n");
	
}

void PlotWindow::OnPaint(wxPaintEvent & event)
{
	wxBufferedPaintDC dc(this);
	dc.SetPen(*wxTRANSPARENT_PEN);
	//dc.DrawRectangle(GetClientRect());
	dc.Clear();
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	
	Render(gc);

	delete gc;

}

void PlotWindow::OnEraseBackground(wxEraseEvent & event)
{
	event.GetDC()->Clear();
}

void PlotWindow::OnResize(wxSizeEvent & event)
{
	for (auto widget : m_widgets)
		widget->Fit();

	Refresh();
	Layout();
}

void PlotWindow::OnLeftDown(wxMouseEvent & event)
{
	int x, y;
	x = event.GetX();
	y = event.GetY();
	//process interaction with on-plot widgets
	for (auto widget : m_widgets)
	{
		if(widget->MouseIsInside(x, y))
		{ 
			widget->MouseButton(WME_LDOWN, x, y);
			return;
		}
	}


	//GetParent()->SetFocus();
	int w, h;
	GetClientSize(&w, &h);
	StartPan((double)x / (double)w, 1- (double)y / (double)h);
	event.Skip();


	if(!HasCapture())
        CaptureMouse();
}

void PlotWindow::OnLeftUp(wxMouseEvent & event)
{
	int x, y;
	x = event.GetX();
	y = event.GetY();

	EndPan();

	for (auto widget : m_widgets)
	{
		if (widget->MouseIsInside(x, y))
		{
			widget->MouseButton(WME_LUP, x, y);
			//return;
		}
	}

	if(HasCapture())
        ReleaseMouse();

}

void PlotWindow::OnMouseMove(wxMouseEvent & event)
{
	int w, h, x, y;
	GetClientSize(&w, &h);
	x = event.GetPosition().x;
	y = event.GetPosition().y;

	for (auto widget : m_widgets)
	{
		if (widget->MouseIsInside(x, y))
		{
			widget->MouseMoving(x, y);
		}
	}

	if (m_panning)
		ProceedPan((double)x / (double)w, 1- y / (double)h);
	//event.Skip();
}

void PlotWindow::OnMouseWheel(wxMouseEvent & event)
{
	int x, y;
	x = event.GetX();
	y = event.GetY();

	double factor;
	if (event.GetWheelRotation() > 0)
		factor = 0.8;
	else
		factor = 1.2;

	//process interaction with on-plot widgets
	for (auto widget : m_widgets)
	{
		if (widget->MouseIsInside(x, y))
		{
			widget->MouseWheel(factor, x, y);
			return;
		}
	}

	

#ifdef _DEBUG
	printf("factor=%f\n", factor);
#endif

	int w, h;
	GetClientSize(&w, &h);
	if(event.GetModifiers() == wxMOD_CONTROL)
		ZoomWheel((double)x / (double)w, (double)y / (double)h, factor, factor);
	else
		if (event.GetModifiers() == wxMOD_SHIFT)
			ZoomWheel((double)x / (double)w, (double)y / (double)h, 1., factor);
		else
			ZoomWheel((double)x / (double)w, (double)y / (double)h, factor, 1.);
}

void PlotWindow::Render(wxGraphicsContext * gc)
{
	DPRINTF("PlotWindow::Render\n");
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	int w, h;
	GetClientSize(&w, &h);
	gc->SetAntialiasMode(wxANTIALIAS_NONE);
	gc->DrawText(m_plot_name, w - 30, 2);
	if (m_spaces.empty())
		return;
//render grid
	Grid *grid;
	grid = m_spaces[0]->GetGrid();
	wxASSERT(grid != NULL);
	grid->Render(gc);

	
//render data
	for (auto space : m_spaces)
	{
		for (auto series : space->GetSerie())
		{
			//
			Renderer *renderer;
			renderer = series->GetRenderer();
			if(renderer != NULL)
				renderer->Render(gc);
		}
	}

	//render widgets
	for (auto widget : m_widgets)
	{
		widget->Render(gc);
	}
}

void PlotWindow::RedrawPlot()
{
	DPRINTF("Plot updated\n");
	Refresh();
	Update();
}

void PlotWindow::GetSize(int * width, int * height)
{
	GetClientSize(width, height);
}

void PlotWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}
