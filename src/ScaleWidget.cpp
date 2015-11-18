#include "ScaleWidget.h"

ScaleWidget::ScaleWidget(Plot * owner, wxOrientation orient) :Widget(owner, NULL)
{

	m_dy = 0;

	m_orient = orient;

	m_height = m_width = 50;

	if (m_pos_rel == wxVERTICAL)
	{
		m_pos_rel = POS_TOPLEFT;
		m_y_anchor = 0;
		m_x_anchor = 0;
	}
	else
	{
		m_pos_rel = POS_BOTTOMLEFT;
		m_y_anchor = 1;
		m_x_anchor = 0;
	}
	Fit();
}

ScaleWidget::~ScaleWidget()
{
}

void ScaleWidget::Fit()
{
	if (m_orient == wxVERTICAL)
	{
		m_owner->GetSize(NULL, &m_height);
		m_height--;
	}
	else
	{
		m_owner->GetSize(&m_width, NULL);
		m_width--;
	}
}

static char s_buff[64];
void ScaleWidget::Render(wxGraphicsContext * gc)
{
	DPRINTF("ScaleWidget::Render\n");

	CalculatetoDCcoords();

	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxTRANSPARENT_BRUSH);
	gc->DrawRectangle(m_widget_x, m_widget_y, m_width, m_height);

	int width, height;

	if (m_orient == wxHORIZONTAL)
	{
		width = m_width;
		height = m_height;
	}
	else
	{
		width = m_height;
		height = m_width;
	}


	if (m_valueadaptor == NULL)
		return;

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
			gc->StrokeLine(x, m_widget_y, x, m_widget_y + tick_len);
		else
			gc->StrokeLine(m_widget_x, x, m_widget_x + tick_len, x);

		m_valueadaptor->ValToStr(s_buff, 20);
		text = s_buff;

		if (m_orient == wxHORIZONTAL)
			gc->DrawText(text, x + fh / 2 + 3, m_widget_y + 7, M_PI / 2. * 3.);
		else
			gc->DrawText(text, m_widget_x + 7, x - fh / 2.);

	}

}

void ScaleWidget::MouseWheel(double factor, int x, int y)
{
	if(m_orient == wxVERTICAL)
		Scale::ZoomAt(1 - (double)y / (double)m_height, factor);
	else
			Scale::ZoomAt((double)x / (double)m_width, factor);
}

void ScaleWidget::proceed_dragging(int x, int y)
{
	if(m_orient == wxVERTICAL)
		Widget::proceed_dragging(x, m_drag_y);
	else
		Widget::proceed_dragging(m_drag_x, y);
}

void ScaleWidget::ScaleRedraw()
{
	DPRINTF("ScaleWidget::ScaleRedraw\n");
	if (m_axes.empty())
		m_owner->RedrawPlot();
}
