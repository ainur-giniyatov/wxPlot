#include "ScaleWidget.h"

ScaleWidget::ScaleWidget(Plot * owner) :Widget(owner, NULL)
{
	m_y_anchor = 0;
	m_dy = 0;
}

ScaleWidget::~ScaleWidget()
{
}

void ScaleWidget::Fit()
{
	m_owner->GetSize(NULL, &m_height);
	m_height--;
	m_width = 20;
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

}

void ScaleWidget::MouseWheel(double factor, int x, int y)
{
	Scale::ZoomAt((double)y / (double)m_height, factor);
}

void ScaleWidget::proceed_dragging(int x, int y)
{
	Widget::proceed_dragging(x, m_drag_y);
}

void ScaleWidget::ScaleRedraw()
{
	DPRINTF("ScaleWidget::ScaleRedraw\n");
}
