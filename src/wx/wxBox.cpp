#include <wx/graphics.h>
#include <wx/dcclient.h>

#include "wx/wxBox.h"
#include "wx/wxPlotWindow.h"

using namespace plot;

wxBox::wxBox()
{
}

wxBox::~wxBox()
{
}

void wxBox::Render(void *vgc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)vgc;
	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);
	gc->DrawRectangle(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());
}

plot::wxTitleBox::wxTitleBox()
{
}

plot::wxTitleBox::~wxTitleBox()
{
}

void plot::wxTitleBox::Render(void *vgc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)vgc;
	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);
	gc->DrawRectangle(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());
	gc->DrawText(wxString(m_title), m_rect.left + m_border_thickness, m_rect.top + m_border_thickness);
}

void plot::wxTitleBox::_ownersize(int w, int h)
{
	wxPlotWindow *plotwindow;
	plotwindow = dynamic_cast<wxPlotWindow *>(m_owner);
	wxClientDC dc(plotwindow);
	wxCoord tw, th;
	dc.GetTextExtent(wxString(m_title), &tw, &th);

	m_rect.SetHeight(th + m_border_thickness * 2);
	m_rect.SetWidth(tw + m_border_thickness * 2);
}
