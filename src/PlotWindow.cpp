//#include "stdafx.h"
#include "PlotWindow.h"
#include "ChartWindow.h"

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(PlotWindow, wxWindow)
EVT_PAINT(PlotWindow::OnPaint)
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
}

PlotWindow::~PlotWindow()
{
	DPRINTF("PlotWindow: dtor\n");
	
}

void PlotWindow::OnPaint(wxPaintEvent & event)
{
	wxBufferedPaintDC dc(this);
	dc.DrawRectangle(GetClientRect());

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

	Render(gc);

	delete gc;

}

void PlotWindow::OnResize(wxSizeEvent & event)
{
	Refresh();

}

void PlotWindow::OnLeftDown(wxMouseEvent & event)
{
	//GetParent()->SetFocus();
	int w, h;
	GetClientSize(&w, &h);
	StartPan((double)event.GetX() / (double)w, (double)event.GetY() / (double)h);
	event.Skip();

	if(!HasCapture())
        CaptureMouse();
}

void PlotWindow::OnLeftUp(wxMouseEvent & event)
{
	EndPan();
	if(HasCapture())
        ReleaseMouse();

}

void PlotWindow::OnMouseMove(wxMouseEvent & event)
{
	int w, h;
	GetClientSize(&w, &h);

	if (m_panning)
		ProceedPan((double)event.GetX() / (double)w, (double)event.GetY() / (double)h);
	//event.Skip();
}

void PlotWindow::OnMouseWheel(wxMouseEvent & event)
{
	double factor;
	if (event.GetWheelRotation() > 0)
		factor = 0.8;
	else
		factor = 1.2;

#ifdef _DEBUG
	printf("factor=%f\n", factor);
#endif

	int w, h;
	GetClientSize(&w, &h);
	if(event.GetModifiers() == wxMOD_CONTROL)
		ZoomWheel((double)event.GetX() / (double)w, (double)event.GetY() / (double)h, factor, factor);
	else
		if (event.GetModifiers() == wxMOD_SHIFT)
			ZoomWheel((double)event.GetX() / (double)w, (double)event.GetY() / (double)h, 1., factor);
		else
			ZoomWheel((double)event.GetX() / (double)w, (double)event.GetY() / (double)h, factor, 1.);
}

void PlotWindow::Render(wxGraphicsContext * gc)
{
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	int w, h;
	GetClientSize(&w, &h);
	gc->DrawText(m_plot_name, w - 30, 2);
	gc->SetAntialiasMode(wxANTIALIAS_NONE);
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
			renderer->Render(gc);
		}
	}

}

void PlotWindow::PlotUpdated()
{
	DPRINTF("Plot updated\n");
	Refresh();
}

void PlotWindow::GetSize(int * width, int * height)
{
	GetClientSize(width, height);
}

Scale * PlotWindow::GetCommonScale()
{
	return ((ChartWindow *)(GetParent()->GetParent()))->GetScaleWindow();
}

void PlotWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}
