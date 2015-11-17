//#include "stdafx.h"
#include <wx/dcbuffer.h>
#include "ScaleWindow.h"

BEGIN_EVENT_TABLE(ScaleWindow, wxPanel)
EVT_PAINT(ScaleWindow::OnPaint)
EVT_ERASE_BACKGROUND(ScaleWindow::OnEraseBackground)
EVT_SIZE(ScaleWindow::OnResize)
EVT_MOUSEWHEEL(ScaleWindow::OnMouseWheel)
EVT_LEFT_DOWN(ScaleWindow::OnLeftDown)
EVT_LEFT_UP(ScaleWindow::OnLeftUp)
EVT_MOTION(ScaleWindow::OnMouseMove)
EVT_MOUSE_CAPTURE_LOST(ScaleWindow::OnMouseCaptureLost)
END_EVENT_TABLE()


ScaleWindow::ScaleWindow(wxWindow *parent, wxOrientation orient, double offset, double range):wxPanel()//(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	SetName("scalewindow");
	m_ispanning = false;

	m_orient = orient;

	if (m_orient == wxHORIZONTAL)
	{
		SetMinClientSize(wxSize(wxDefaultCoord, 120));
	}
	else
	{
		SetMinClientSize(wxSize(50, wxDefaultCoord));
	}

	m_offset = offset;
	m_range = range;
}


ScaleWindow::~ScaleWindow()
{
}


void ScaleWindow::ScaleRedraw()
{
	Refresh();
	Update();
}

static char s_buff[20];

void ScaleWindow::OnPaint(wxPaintEvent & event)
{
	DPRINTF("ScaleWindow::OnPaint\n");
	int width, height;
	
	if(m_orient == wxHORIZONTAL)
		GetClientSize(&width, &height);
	else
		GetClientSize(&height, &width);

	wxBufferedPaintDC dc(this);
	wxRect rect;
	rect = GetClientRect();
	//wxColor col(255, 212, 127, 50);
	//
	//dc.SetPen(col);
	//dc.SetBrush(col);
	//dc.DrawRectangle(rect);
	dc.Clear();

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
		if (m_orient == wxVERTICAL)
			x = width - x;
		if (x < 0)
			continue;
		if (x > width)
			break;
		tick_len = 5.; 

		if (m_orient == wxHORIZONTAL)
			gc->StrokeLine(x, 0, x, tick_len);
		else
			gc->StrokeLine(0, x, tick_len, x);

		m_valueadaptor->ValToStr(s_buff, 20);
		text = s_buff;

		if (m_orient == wxHORIZONTAL)
			gc->DrawText(text, x + fh / 2 + 3, 7, M_PI / 2. * 3.);
		else
			gc->DrawText(text, 7, x - fh / 2.);

	}

	delete gc;
}

void ScaleWindow::OnEraseBackground(wxEraseEvent & event)
{
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
	int w, h;
	GetClientSize(&w, &h);
	if (m_orient == wxHORIZONTAL)
		ZoomAt((double)event.GetX() / (double)w, factor);
	else
		ZoomAt(1 - (double)event.GetY() / (double)h, factor);
}

void ScaleWindow::OnLeftDown(wxMouseEvent & event)
{
	SetFocus();
	int x, h;
	GetClientSize(&x, &h);
	m_ispanning = true;

	if (m_orient == wxHORIZONTAL)
		StartPanAt((double)event.GetX() / (double)x);
	else
		StartPanAt(1 - (double)event.GetY() / (double)h);

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
	int x, h;
	GetClientSize(&x, &h);
	if (m_ispanning)
	{
		if (m_orient == wxHORIZONTAL)
			ProceedPanAt((double)event.GetX() / (double)x);
		else
			ProceedPanAt(1 - (double)event.GetY() / (double)h);
	}
}

void ScaleWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}
