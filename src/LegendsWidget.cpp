#include "LegendsWidget.h"
#include "PlotWindow.h"

#define TEXT_MARGIN 4

LegendsWidget::LegendsWidget(Plot * owner): Widget(owner)
{
}

LegendsWidget::~LegendsWidget()
{
}

void LegendsWidget::Fit()
{
	wxClientDC dc((PlotWindow *)m_owner);

	m_width = 50;
	m_height = 0;
	bool empty;
	empty = true;
	for (auto space : m_owner->GetSpaces())
	{
		for (auto series : space->GetSerie())
		{
			wxCoord text_w, text_h;
			dc.GetTextExtent(wxString(series->GetSeriesName()), &text_w, &text_h);
			m_height += text_h;
			if (m_width < text_w + TEXT_MARGIN)
				m_width = text_w + TEXT_MARGIN;

			empty = false;
		}
	}
	if (empty)
		m_height = 5;
	/*else
		m_height += TEXT_MARGIN;*/

}

void LegendsWidget::Render(wxGraphicsContext * gc)
{
	Fit();
	Widget::Render(gc);
	wxCoord hpos = 0;
	for (auto space : m_owner->GetSpaces())
	{
		for (auto series : space->GetSerie())
		{
			wxString text(series->GetSeriesName());
			wxDouble text_h;
			gc->GetTextExtent(text, NULL, &text_h);
			gc->DrawText(text, m_widget_x + TEXT_MARGIN, m_widget_y + hpos);
			hpos += text_h;
		}
	}
}
