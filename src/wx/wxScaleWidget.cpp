//#include "stdafx.h"
#include <algorithm>
#include <math.h>

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "wx/wxScaleWidget.h"
#include "wx/wxSubPlot.h"

using namespace plot;

BEGIN_EVENT_TABLE(wxScaleWidget, wxPanel)
EVT_PAINT(wxScaleWidget::OnPaint)
EVT_ERASE_BACKGROUND(wxScaleWidget::OnEraseBackground)
EVT_SIZE(wxScaleWidget::OnResize)
EVT_MOUSEWHEEL(wxScaleWidget::OnMouseWheel)
EVT_LEFT_DOWN(wxScaleWidget::OnLeftDown)
EVT_LEFT_UP(wxScaleWidget::OnLeftUp)
EVT_MOTION(wxScaleWidget::OnMouseMove)
EVT_MOUSE_CAPTURE_LOST(wxScaleWidget::OnMouseCaptureLost)
END_EVENT_TABLE()


wxScaleWidget::wxScaleWidget(wxWindow *parent, AXIS_DIR axis_dir, wxOrientation orient, wxEdge scale_pos, double offset, double range):wxPanel()
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER);

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
	
	m_scale_position = scale_pos;

}


wxScaleWidget::~wxScaleWidget()
{
	delete m_scale;
}

int plot::wxScaleWidget::_getscalephysicalrange()
{
	int phrange = 0;
	wxSize sz = GetSize();
	
	if (m_orient == wxVERTICAL)
		phrange = sz.GetHeight();
	
	if (m_orient == wxHORIZONTAL)
		phrange = sz.GetWidth();

	return phrange;
}


//void wxScaleWidget::ScaleRedraw()
//{
//	Refresh();
//	Update();
//}

static char s_buff[64];

void wxScaleWidget::OnPaint(wxPaintEvent & event)
{
	int min_size = 20;
	DPRINTF("wxScaleWidget::OnPaint\n");
	int width, height;

	if (m_orient == wxHORIZONTAL)
		GetClientSize(&width, &height);
	else
		GetClientSize(&height, &width);

	wxBufferedPaintDC dc(this);
	wxRect rect;
	rect = GetClientRect();
	wxColor col(210, 255, 138);
	//
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(col);
	dc.DrawRectangle(rect);
	//dc.Clear();
	
	auto valadaptor = m_scale->GetValueAdaptor();
	
	if (valadaptor == nullptr)
		return;

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	gc->SetFont(m_font, *wxBLACK);
	wxString text;
	wxDouble fw, fh;

	gc->SetPen(*wxBLACK_PEN);

	if (m_scale_position == wxBottom)
		gc->StrokeLine(0, 0, width, 0);

	if (m_scale_position == wxTop)
		gc->StrokeLine(0, height, width, height);

	if (m_scale_position == wxLeft)
		gc->StrokeLine(height - 1, 0, height - 1, width);

	if (m_scale_position == wxRight)
		gc->StrokeLine(0, 0, 0, height);


	int x;
	bool isbold;
	double m_offset = m_scale->GetOffset();
	double m_range = m_scale->GetRange();

	wxString format_string = " %.2f";

	char buf[128];
	valadaptor->ValToStr(buf, 128, m_offset);
	gc->GetTextExtent(wxString(buf), &fw, &fh);


	valadaptor->InitState(m_offset, m_range, fw / (double)width);

	if (m_orient == wxHORIZONTAL)
	{
		valadaptor->InitState(m_offset, m_range, (fw + 5.) / (double)width);
	}
	else
	{
		valadaptor->InitState(m_offset, m_range, (fh + 5.) / (double)width);
	}

	gc->SetPen(*wxBLACK_PEN);
	while (valadaptor->MajorStep())
	{
	
		int tick_len;

		x = valadaptor->GetMajorTick() / m_range * width;

		tick_len = 8.; 

		if (m_orient == wxVERTICAL)
			x = width - x;

		//tick labels
		valadaptor->ValToStr(buf, 50);
		text = wxString(buf);

		gc->GetTextExtent(text, &fw, &fh);

		gc->SetFont(m_font, *wxBLACK);
		if (m_orient == wxHORIZONTAL)
			gc->DrawText(text, x - fw / 2, 10);
		else
		{
			if (m_scale_position == wxLeft)
			{
				gc->DrawText(text, height - 10 - 1 - fw, x - fh / 2.);
			}
			else
				assert(0);
		}

		//major ticks
		if (m_orient == wxHORIZONTAL)
			gc->StrokeLine(x, 0, x, tick_len);
		else
		{
			if (m_scale_position == wxLeft)
				gc->StrokeLine(height - 1, x, height - tick_len - 1, x);
			else
				assert(0);
		}
	
		//minor ticks
		while (valadaptor->MinorStep())
		{
			x = valadaptor->GetMinorTick() / m_range * width;

			tick_len = valadaptor->IsMiddleMinor() ? 5 : 2;

			if (m_orient == wxVERTICAL)
				x = width - x;

			if (m_orient == wxHORIZONTAL)
				gc->StrokeLine(x, 0, x, tick_len);
			else
			{
				if (m_scale_position == wxLeft)
					gc->StrokeLine(height - 1, x, height - tick_len - 1, x);
				else
					assert(0);
			}
		}

		if (m_orient == wxHORIZONTAL)
		{
			if (min_size < fh + 8)
				min_size = fh + 8;
		}
		else
		{
			if (min_size < fw + 8)
				min_size = fw + 8;
		}

		//if (!valadaptor->MajorStep())
		//	break;
	}

	//if (valadaptor->ValBiggerPart(s_buff, 64))
	//{
	//	m_font.MakeBold();
	//	gc->SetFont(m_font, *wxBLACK);
	//	gc->GetTextExtent(s_buff, &fw, &fh);
	//	gc->DrawText(s_buff, (width - fw) / 2., height - fh - 1);
	//}

	delete gc;


	m_size_recalculated = min_size;

}

void wxScaleWidget::OnEraseBackground(wxEraseEvent & event)
{
	auto dc = event.GetDC();
	dc->SetBrush(GetBackgroundColour());
	dc->DrawRectangle(GetClientRect());
}

void wxScaleWidget::OnResize(wxSizeEvent & event)
{
	Refresh();
	event.Skip();
}

void wxScaleWidget::OnMouseWheel(wxMouseEvent & event)
{
	double factor;
	if (event.GetWheelRotation() > 0)
		factor = 0.8;
	else
		factor = 1.2;

	DPRINTF("wxScaleWidget::OnMouseWheel\n");
	int w, h;
	GetClientSize(&w, &h);
	if (m_orient == wxHORIZONTAL)
		m_scale->ZoomAt((double)event.GetX() / (double)w, factor);
	else
		m_scale->ZoomAt(1 - (double)event.GetY() / (double)h, factor);

	validate();

	auto clsize = GetClientSize();
	if (m_orient == wxHORIZONTAL && clsize.y != m_size_recalculated)
	{
		SetMinClientSize(wxSize(wxDefaultCoord, m_size_recalculated + 5));
		GetParent()->Layout();
	}

	if (m_orient == wxVERTICAL && clsize.x != m_size_recalculated)
	{
		SetMinClientSize(wxSize(m_size_recalculated + 5, wxDefaultCoord));
		GetParent()->Layout();
	}
	
}

void wxScaleWidget::OnLeftDown(wxMouseEvent & event)
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

void wxScaleWidget::OnLeftUp(wxMouseEvent & event)
{
	m_scale->EndPanAt();
	m_ispanning = false;

	wxCommandEvent eventvc(PLOTVIEWCHANGED, GetId());
	eventvc.SetEventObject(this);
	ProcessWindowEvent(eventvc);

	if(HasCapture())
        ReleaseMouse();
}

void wxScaleWidget::OnMouseMove(wxMouseEvent & event)
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

void wxScaleWidget::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}

void plot::wxScaleWidget::validate()
{

	for (auto plot : m_scale->_get_plots())
		plot->Validate();

	Refresh();
	Update();
}

void plot::wxScaleWidget::MyScale::Validate()
{
	m_me->Refresh();
	m_me->Update();
};
