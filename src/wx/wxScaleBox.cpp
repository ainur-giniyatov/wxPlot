#include "wx/wxScaleBox.h"

using namespace plot;

wxScaleBox::wxScaleBox(wxPlotWindow * plot, Dir orient):Box(plot), Scale()
{
	m_owner = plot;
	m_flag_expand_dir = orient;
	m_orient = orient;
	m_snap_offset = 0;
	if (m_orient == DIR_HOR)
		m_sticked_to |= STICKEDTO_BOTTOM;
	m_isresizable = false;
	m_owner->AddBox(this);
	Sizing();
}

wxScaleBox::~wxScaleBox()
{
}

static char s_buff[64];
void wxScaleBox::Render(void * v_gc)
{
	DPRINTF("wxScaleBox::Render\n");
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	//wxBrush brush;
	//brush.SetColour(((wxPlotWindow *)m_owner)->GetBackgroundColour());
	//gc->SetBrush(brush);
	//gc->DrawRectangle(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());

	int width, height;

	if (m_orient & DIR_HOR)
	{
		width = m_rect.Width();
		height = m_rect.Height();
	}
	else
	{
		width = m_rect.Height();
		height = m_rect.Width();
	}


	if (m_valueadaptor == NULL)
		return;

	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	wxString text;
	wxDouble fh, fw;
	
	int x;
	bool isbold;

	m_valueadaptor->InitState(m_offset, m_range, 15. / (double)width);
	gc->SetPen(*wxBLACK_PEN);
	wxGraphicsBrush gbrush = gc->CreateBrush(*wxWHITE_BRUSH);// wxBrush(((wxPlotWindow *)m_owner)->GetBackgroundColour()));

	while (m_valueadaptor->Step())
	{
		double ticker = m_valueadaptor->GetTicker();
		int tick_len;
		x = (ticker) / m_range * width;
		if (m_orient & DIR_VER)
			x = width - x;
		if (x < 0)
			continue;
		if (x > width)
			break;
		tick_len = 5.;

		/*if (m_orient == wxHORIZONTAL)
		gc->StrokeLine(x, m_widget_y, x, m_widget_y + tick_len);
		else
		gc->StrokeLine(m_widget_x, x, m_widget_x + tick_len, x);*/

		m_valueadaptor->ValToStr(s_buff, 20);
		text = wxString::Format(" %s ", s_buff);

		gc->GetTextExtent(text, &fw, &fh);
		wxDouble align_offset = 0;
		
		if (!(m_orient & DIR_HOR) && (m_sticked_to & STICKEDTO_RIGHT) )
			align_offset = fw - 7;

		if ((m_orient & DIR_HOR) && (m_sticked_to & STICKEDTO_BOTTOM))
			align_offset = fw - 7;

		if (m_orient & DIR_HOR)
			gc->DrawText(text, x + fh / 2 + 3, m_rect.top + 7 - align_offset, M_PI / 2. * 3., gbrush);
		else
			gc->DrawText(text, m_rect.left + 7 - align_offset, x - fh / 2., gbrush);

	}

}

void wxScaleBox::ScaleRedraw()
{
}
