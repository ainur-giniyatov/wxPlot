//#include "stdafx.h"
#include <wx/dcbuffer.h>
#include "ScaleWindow.h"

BEGIN_EVENT_TABLE(ScaleWindow, wxPanel)
EVT_PAINT(ScaleWindow::OnPaint)
EVT_SIZE(ScaleWindow::OnResize)
EVT_MOUSEWHEEL(ScaleWindow::OnMouseWheel)
EVT_LEFT_DOWN(ScaleWindow::OnLeftDown)
EVT_LEFT_UP(ScaleWindow::OnLeftUp)
EVT_MOTION(ScaleWindow::OnMouseMove)
EVT_MOUSE_CAPTURE_LOST(ScaleWindow::OnMouseCaptureLost)
END_EVENT_TABLE()


ScaleWindow::ScaleWindow(wxWindow *parent):wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	SetName("scalewindow");
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_ispanning = false;
}


ScaleWindow::~ScaleWindow()
{
}

void ScaleWindow::ScaleUpdated()
{
	Scale::ScaleUpdated();
	GetParent()->Refresh();
	GetParent()->Update();

}

static char s_buff[20];

void ScaleWindow::OnPaint(wxPaintEvent & event)
{
	int width, height;
	GetClientSize(&width, &height);
	wxBufferedPaintDC dc(this);
	wxRect rect;
	rect = GetClientRect();
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(rect);
	if (m_valueadaptor == NULL)
		return;

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	wxString text("text");
	wxDouble fh;
	gc->GetTextExtent("A", NULL, &fh);

	int x;
	bool isbold;

	m_valueadaptor->InitState(m_offset, m_range, 15. / (double)width);
	gc->SetPen(*wxBLACK_PEN);

	while (m_valueadaptor->Step())
	{
		double ticker = m_valueadaptor->GetTicker();
		int tick_len;
		x = (ticker) / m_range * width;
		if (x < 0)
			continue;
		if (x > width)
			break;
		tick_len = 5.; 
		gc->StrokeLine(x, 0, x, tick_len);

		m_valueadaptor->ValToStr(s_buff, 20, ticker + m_offset);
		text = s_buff;

		gc->DrawText(text, x + fh / 2 + 3, 7, M_PI / 2. * 3.);

	}

	delete gc;
}

void ScaleWindow::OnResize(wxSizeEvent & event)
{
	Refresh();
}

void ScaleWindow::OnMouseWheel(wxMouseEvent & event)
{
	double factor;
	if (event.GetWheelRotation() > 0)
		factor = 0.8;
	else
		factor = 1.2;

	DPRINTF("ScaleWindow::OnMouseWheel\n");
	int w;
	GetClientSize(&w, NULL);
	ZoomAt((double)event.GetX() / (double)w, factor);

}

void ScaleWindow::OnLeftDown(wxMouseEvent & event)
{
	SetFocus();
	int x;
	GetClientSize(&x, NULL);
	m_ispanning = true;
	StartPanAt((double)event.GetX() / (double)x);

	if(!HasCapture())
        CaptureMouse();
}

void ScaleWindow::OnLeftUp(wxMouseEvent & event)
{
	EndPanAt();
	m_ispanning = false;
	if(HasCapture())
        ReleaseMouse();
}

void ScaleWindow::OnMouseMove(wxMouseEvent & event)
{
	int x;
	GetClientSize(&x, NULL);
	if(m_ispanning)
		ProceedPanAt((double)event.GetX() / (double)x);
}

void ScaleWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}
