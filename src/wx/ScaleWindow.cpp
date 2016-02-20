//#include "stdafx.h"
#include <algorithm>

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "wx/ScaleWindow.h"
#include "wx/wxPlotWindow.h"

using namespace plot;

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


ScaleWindow::ScaleWindow(wxWindow *parent, AXIS_DIR axis_dir, wxOrientation orient, double offset, double range):wxPanel()
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	SetName("scalewindow");
	m_ispanning = false;

	m_orient = orient;

	if (m_orient == wxHORIZONTAL)
	{
		SetMinClientSize(wxSize(wxDefaultCoord, 70));
	}
	else
	{
		SetMinClientSize(wxSize(50, wxDefaultCoord));
	}

	m_scale = new MyScale(this, axis_dir);
	m_scale->SetOffset(offset);
	m_scale->SetRange(range);

	m_font = *wxNORMAL_FONT;
}


ScaleWindow::~ScaleWindow()
{
	delete m_scale;
}


//void ScaleWindow::ScaleRedraw()
//{
//	Refresh();
//	Update();
//}

static char s_buff[64];

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

	if (m_scale->GetValueAdaptor() == NULL)
		return;

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->SetFont(m_font, *wxBLACK);
	wxString text("text");
	wxDouble fw, fh;
	gc->GetTextExtent("A", &fw, &fh);

	int x;
	bool isbold;
	double m_offset = m_scale->GetOffset();
	double m_range = m_scale->GetRange();

	m_scale->GetValueAdaptor()->InitState(m_offset, m_range, 15. / (double)width);
	gc->SetPen(*wxBLACK_PEN);

	while (m_scale->GetValueAdaptor()->Step())
	{
		double ticker = m_scale->GetValueAdaptor()->GetTicker();
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

		m_scale->GetValueAdaptor()->ValToStr(s_buff, 64);
		text = s_buff;
		if(m_scale->GetValueAdaptor()->IsBold())
		{ 
			m_font.MakeBold();
		}
		else
		{ 
			m_font = *wxNORMAL_FONT;
		}
		gc->SetFont(m_font, *wxBLACK);
		if (m_orient == wxHORIZONTAL)
			gc->DrawText(text, x + fh / 2 + 3, 7, M_PI / 2. * 3.);
		else
			gc->DrawText(text, 7, x - fh / 2.);

	}

	if (m_scale->GetValueAdaptor()->ValBiggerPart(s_buff, 64))
	{
		m_font.MakeBold();
		gc->SetFont(m_font, *wxBLACK);
		gc->GetTextExtent(s_buff, &fw, &fh);
		gc->DrawText(s_buff, (width - fw) / 2., height - fh - 1);
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
		m_scale->ZoomAt((double)event.GetX() / (double)w, factor);
	else
		m_scale->ZoomAt(1 - (double)event.GetY() / (double)h, factor);

	validate();
}

void ScaleWindow::OnLeftDown(wxMouseEvent & event)
{
	SetFocus();
	int x, h;
	GetClientSize(&x, &h);
	m_ispanning = true;

	if (m_orient == wxHORIZONTAL)
		m_scale->StartPanAt((double)event.GetX() / (double)x);
	else
		m_scale->StartPanAt(1 - (double)event.GetY() / (double)h);

	if(!HasCapture())
        CaptureMouse();
}

void ScaleWindow::OnLeftUp(wxMouseEvent & event)
{
	m_scale->EndPanAt();
	m_ispanning = false;

	wxCommandEvent eventvc(PLOTVIEWCHANGED, GetId());
	eventvc.SetEventObject(this);
	ProcessWindowEvent(eventvc);

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
			m_scale->ProceedPanAt((double)event.GetX() / (double)x);
		else
			m_scale->ProceedPanAt(1 - (double)event.GetY() / (double)h);
		validate();
	}
}

void ScaleWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}

void plot::ScaleWindow::validate()
{

	for (auto plot : m_scale->_get_plots())
		plot->Validate();

	Refresh();
	Update();
}

void plot::ScaleWindow::MyScale::Validate()
{
	m_me->Refresh();
	m_me->Update();
};
