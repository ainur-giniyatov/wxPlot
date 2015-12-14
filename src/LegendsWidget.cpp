#include "LegendsWidget.h"
#include "PlotWindow.h"

#define TEXT_MARGIN 4

const int LegendsWidget::ID_MENU_DELETE_SERIES = wxNewId();

BEGIN_EVENT_TABLE(LegendsWidget, Widget)
EVT_MENU(LegendsWidget::ID_MENU_DELETE_SERIES, LegendsWidget::OnMenuDeleteSeries)
END_EVENT_TABLE()

LegendsWidget::LegendsWidget(Plot * owner): Widget(owner)
{
	//m_menuitem_delete_widget = m_menu.Append(ID_MENU_DELETE_SERIES, "Delete this series");
	m_menuitem_delete_widget = new wxMenuItem(NULL, ID_MENU_DELETE_SERIES, "Delete");
	m_pointed_series = NULL;
}

LegendsWidget::~LegendsWidget()
{
	delete m_menuitem_delete_widget;
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

void LegendsWidget::OnMouseRightUp(int x, int y)
{
	m_pointed_series = NULL;

	int y_c = m_widget_y;

	wxClientDC dc((PlotWindow *)m_owner);
	
	for (auto space : m_owner->GetSpaces())
	{
		for (auto series : space->GetSerie())
		{
			wxCoord text_w, text_h;
			dc.GetTextExtent(wxString(series->GetSeriesName()), &text_w, &text_h);

			if (y_c < y && (y_c + text_h) > y)
			{
				m_pointed_series = series;
				break;
			}
			y_c += text_h;
		}
	}

	if (m_pointed_series != NULL)
	{
		m_menuitem_delete_widget->SetItemLabel(wxString::Format("Delete %s", m_pointed_series->GetSeriesName()));
		m_menu.Append(m_menuitem_delete_widget);
		Widget::OnMouseRightUp(x, y);
		m_menu.Remove(m_menuitem_delete_widget);
	}
	else
	{
		Widget::OnMouseRightUp(x, y);
	}


}

void LegendsWidget::OnMenuDeleteSeries(wxCommandEvent & event)
{
	DPRINTF("LegendsWidget::OnMenuDeleteSeries\n");


	if (m_pointed_series != NULL)
	{
#ifdef _DEBUG
		printf("series: %s\n", m_pointed_series->GetSeriesName());
		delete m_pointed_series;
		m_pointed_series = NULL;
#endif
	}
	else
	{
		DPRINTF("Not found\n");
	}
}
