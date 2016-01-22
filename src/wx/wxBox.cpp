#include <wx/dcclient.h>
#include <wx/graphics.h>
#include "wx/wxBox.h"

using namespace plot;

const int wxBox::IDMENUITEM_CLOSE = wxNewId();

wxBox::wxBox(wxPlotWindow * plotwindow):wxEvtHandler(), Box(plotwindow)
{
	DPRINTF("wxBox ctor\n");

	m_owner->RedrawPlot();

	m_menu.SetNextHandler(this);
	m_menu.Append(IDMENUITEM_CLOSE, "Close");

	wxEvtHandler::Connect(IDMENUITEM_CLOSE, wxEVT_MENU, (wxObjectEventFunction)&wxBox::OnMenu_Close);
}

wxBox::~wxBox()
{
	DPRINTF("wxBox dtor\n");
	wxEvtHandler::Disconnect(IDMENUITEM_CLOSE, wxEVT_MENU, (wxObjectEventFunction)&wxBox::OnMenu_Close);
}

void wxBox::Render(void *v_gc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	wxPen pen(*wxBLACK_PEN);
	pen.SetWidth(m_border_thickness);
	gc->SetPen(pen);
	gc->SetBrush(*wxWHITE_BRUSH);
	int w, h;
	w = m_rect.Width();
	h = m_rect.Height();
	gc->DrawRectangle(m_rect.left, m_rect.top, w, h);
	//gc->StrokeLine(p1.x, p1.y, p2.x, p1.y);
	//gc->StrokeLine(p2.x, p1.y, p2.x, p2.y);
	//gc->StrokeLine(p2.x, p2.y, p1.x, p2.y);
	//gc->StrokeLine(p1.x, p2.y, p1.x, p1.y);
}

void plot::wxBox::MouseRightUp(int mx, int my)
{
	((wxPlotWindow*)m_owner)->PopupMenu(&m_menu);
}

void plot::wxBox::OnMenu_Close(wxCommandEvent & event)
{
	CallAfter(&wxBox::deletebox);
}

void plot::wxBox::deletebox()
{
	m_owner->DeleteBox(this);
}

/*TiteBox*/
wxTitleBox::wxTitleBox(wxPlotWindow * plotwindow):wxBox(plotwindow)
{
	m_title = wxString::Format("%s", plotwindow->GetPlotName());
	m_sticked_to = STICKEDTO_TOP | STICKEDTO_HOR_CENTER;
	Sizing();
}

wxTitleBox::~wxTitleBox()
{

}

void wxTitleBox::Render(void * v_gc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	m_title = wxString::Format("%s", ((wxPlotWindow *)m_owner)->GetPlotName());
	gc->DrawText(m_title, m_rect.left + 3, m_rect.top + 3);
}

void wxTitleBox::Sizing()
{
	wxClientDC dc((wxPlotWindow *)m_owner);
	wxCoord t_w, t_h;
	dc.GetTextExtent(m_title, &t_w, &t_h);

	m_rect.right = m_rect.left + t_w + 6;
	m_rect.bottom = m_rect.top + t_h + 6;

	Box::Sizing();
}

plot::wxLegendsBox::wxLegendsBox(wxPlotWindow * plotwindow):LegendsBox(plotwindow)
{
	margin = 3;
	Sizing();
}

plot::wxLegendsBox::~wxLegendsBox()
{
}

void wxLegendsBox::MouseRightUp(int mx, int my)
{
	DPRINTF("wxLegendsBox::MouseRightUp");
	Point<int> mp;
	mp = Point<int>(mx - m_rect.left, my - m_rect.top);
	for (auto item_iter : m_items)
	{
		if (item_iter->m_rect.IsInside(mp))
		{
			((wxPlotWindow *)m_owner)->_popup_seriesmenu(item_iter->m_series);
			break;
		}
	}
}

void plot::wxLegendsBox::Render(void *v_gc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	gc->SetPen(*wxBLUE_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);
	int w, h;
	w = m_rect.Width();
	h = m_rect.Height();
	gc->DrawRectangle(m_rect.left, m_rect.top, w, h);

	int tx = margin +  margin + 28, ty = margin;
	
	for (auto item : m_items)
	{
		wxString text(item->m_series->GetSeriesName());
		wxDouble tw, th;
		gc->GetTextExtent(text, &tw, &th);
		gc->DrawText(text, m_rect.left + tx, m_rect.top + ty);

		if (item->m_series->GetRenderer()->GetVisible())
		{
			if (item->m_series->GetRenderer()->GetLineVisible())
				item->m_series->GetRenderer()->PutLine(gc, m_rect.left + margin, m_rect.top + ty + th / 2., 28, 0);
			if (item->m_series->GetRenderer()->GetMarksVisible())
				item->m_series->GetRenderer()->PutMark(gc, m_rect.left + margin + 28 / 2, m_rect.top + ty + th / 2.);
		}
		else
		{

		}
		ty += th + margin;
		//gc->SetBrush(*wxTRANSPARENT_BRUSH);
		//gc->DrawRectangle(item->m_rect.left + m_rect.left, item->m_rect.top + m_rect.top, item->m_rect.Width(), item->m_rect.Height());
	}

}

void plot::wxLegendsBox::Sizing()
{
	
	int w = 15, h = margin;
	wxClientDC dc((wxPlotWindow *)m_owner);
	dc.SetFont(*wxNORMAL_FONT);
	if (m_items.empty())
		w = h = 10;

	for (auto item : m_items)
	{
		wxString text(item->m_series->GetSeriesName());
		wxCoord tw, th;
		dc.GetTextExtent(text, &tw, &th);
		if (w < tw)
			w = tw;
		item->m_rect.left = margin;
		
		item->m_rect.top = h;
		item->m_rect.bottom = item->m_rect.top + th;
		h += th + margin;
	}

	for (auto item : m_items)
		item->m_rect.right = item->m_rect.left + 28 + margin + w;

	w +=  margin + margin + margin + 28;

	m_rect.right = m_rect.left + w;
	m_rect.bottom = m_rect.top + h;

	Box::Sizing();
}
